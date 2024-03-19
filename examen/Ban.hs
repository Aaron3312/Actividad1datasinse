import Data.Char (isDigit, isLetter)
import Data.List (intercalate)

data Token
  = Entero String
  | Real String
  | Asignacion
  | Variable String
  | Comentario String
  | Operador String
  | Multiplicacion
  | Division
  | Suma
  | Resta
  | Potencia
  | ParentesisOpen
  | ParentesisCierre
  deriving (Show)

type LineNumber = Int
type ValidationResult = Either String [Token]

lexer :: String -> [Token]
lexer [] = []
lexer ('/':'/':cs) = [Comentario ('/':'/':cs)]
lexer (c:cs)
  | isDigit c || (c == '-' && not (null cs) && (isDigit (head cs) || head cs == '.')) = lexNumberOrReal (c:cs)
  | isLetter c || c == '_' = lexIdentifier (c:cs)
  | c == '=' = Asignacion : lexer cs
  | elem c "+-*/^" = Operador [c] : lexer cs
  | c == '(' = ParentesisOpen : lexer cs
  | c == ')' = ParentesisCierre : lexer cs
  | otherwise = lexer cs

lexNumberOrReal :: String -> [Token]
lexNumberOrReal cs =
  let (num, rest) = span (\x -> isDigit x || x == '.' || x == 'E' || x == 'e' || x == '-') cs
   in if elem '.' num || elem 'E' num || elem 'e' num
      then Real num : lexer rest
      else Entero num : lexer rest

lexIdentifier :: String -> [Token]
lexIdentifier cs =
  let (ident, rest) = span (\x -> isDigit x || isLetter x || x == '_') cs
   in Variable ident : lexer rest

tokenToString :: Token -> String
tokenToString token = case token of
  Entero n -> "Entero\t\t" ++ n
  Real n -> "Real\t\t" ++ n
  Asignacion -> "Asignacion\t="
  Variable ident -> "Variable\t" ++ ident
  Comentario c -> "Comentario\t" ++ c
  Operador op -> "Operador\t" ++ op
  Multiplicacion -> "Multiplicacion\t*"
  Division -> "Division\t/"
  Suma -> "Suma\t\t+"
  Resta -> "Resta\t\t-"
  Potencia -> "Potencia\t^"
  ParentesisOpen -> "ParentesisAbre\t("
  ParentesisCierre -> "ParentesisCierra\t)"

tokensToTable :: [Token] -> String
tokensToTable tokens =
  let headers = "Tipo\tValor\n" ++ replicate 50 '-'
      rows = map tokenToString tokens
   in headers ++ "\n" ++ intercalate "\n" rows

processAndValidateLines :: [String] -> [(LineNumber, ValidationResult)]
processAndValidateLines lines = zipWith (\n line -> (n, validateLineTokens (lexer line))) [1..] lines

validateLineTokens :: [Token] -> ValidationResult
validateLineTokens tokens
  | null tokens = Left "Línea vacía o comentario"
  | not $ validarParentesis tokens 0 = Left "Desequilibrio de paréntesis"
  | otherwise = Right tokens

validarParentesis :: [Token] -> Int -> Bool
validarParentesis [] 0 = True
validarParentesis [] _ = False
validarParentesis (ParentesisOpen:ts) n = validarParentesis ts (n + 1)
validarParentesis (ParentesisCierre:ts) n = n > 0 && validarParentesis ts (n - 1)
validarParentesis (_:ts) n = validarParentesis ts n

reportValidationResults :: [(LineNumber, ValidationResult)] -> IO ()
reportValidationResults results = mapM_ reportResult results
  where
    reportResult (lineNum, Right _) = putStrLn $ "Línea " ++ show lineNum ++ ": Válida"
    reportResult (lineNum, Left errorMsg) = putStrLn $ "Línea " ++ show lineNum ++ ": Error - " ++ errorMsg

main :: IO ()
main = do
  putStrLn "Analizando el archivo input.txt..."
  contents <- readFile "input.txt"
  let linesOfContents = lines contents
  let validationResults = processAndValidateLines linesOfContents
  reportValidationResults validationResults
  let validTokens = [tokens | (_, Right tokens) <- validationResults]
  writeFile "output.txt" (intercalate "\n\n" $ map tokensToTable validTokens)
  putStrLn "Análisis y escritura completados."

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

lexer :: String -> [Token]
lexer [] = []
lexer ('/':'/':cs) = [Comentario ('/':'/':cs)]
lexer (c:cs)
  | isDigit c || (c == '-' && not (null cs) && (isDigit (head cs) || head cs == '.')) = lexNumberOrReal (c:cs)
  | isLetter c || c == '_' = lexIdentifier (c:cs)
  | c == '=' = Asignacion : lexer cs
  | c == '+' = Operador "+" : lexer cs
  | c == '-' = Operador "-" : lexer cs
  | c == '*' = Operador "*" : lexer cs
  | c == '/' = Operador "/" : lexer cs
  | c == '(' = ParentesisOpen : lexer cs
  | c == ')' = ParentesisCierre : lexer cs
  | c == '^' = Operador "^" : lexer cs
  | otherwise = lexer cs

lexNumberOrReal :: String -> [Token]
lexNumberOrReal cs =
  let (num, rest) = span (\x -> isDigit x || x == '.' || x == 'E' || x == 'e' || x == '-') cs
   in if 'E' `elem` num || 'e' `elem` num || '.' `elem` num
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
  ParentesisOpen -> "ParentesisAbre\t("
  ParentesisCierre -> "ParentesisCierra\t)"
  _ -> "Otro\t\t"

tokensToTable :: [Token] -> String
tokensToTable tokens =
  let headers = "Tipo\t\tValor\n" ++ replicate 40 '-'
      rows = map tokenToString tokens
   in headers ++ "\n" ++ intercalate "\n" rows

type LineNumber = Int
type ValidationResult = Either String [Token]

processAndValidateLines :: [String] -> [(LineNumber, ValidationResult)]
processAndValidateLines lines =
  zipWith (\n line -> (n, validateLineTokens (lexer line))) [1..] lines

validateLineTokens :: [Token] -> ValidationResult
validateLineTokens tokens =
  if null tokens
  then Left "Línea vacía o comentario"
  else Right tokens

reportValidationResults :: [(LineNumber, ValidationResult)] -> IO ()
reportValidationResults results = mapM_ printResult results
  where
    printResult (n, Right _) = putStrLn $ "Línea " ++ show n ++ ": Válida"
    printResult (n, Left msg) = putStrLn $ "Línea " ++ show n ++ ": Error - " ++ msg

main :: IO ()
main = do
  contents <- readFile "input.txt"
  let linesOfContents = lines contents
  let validationResults = processAndValidateLines linesOfContents
  reportValidationResults validationResults
  let validTokens = [tokens | (_, Right tokens) <- validationResults]
  writeFile "output.txt" (intercalate "\n\n" $ map tokensToTable validTokens)
  putStrLn "Análisis y escritura completados."

import Data.Char (isDigit, isLetter)
import Data.List (intercalate)
import Data.Array.IO (writeArray)

data Token
  = Entero String
  | Division
  | Suma
  | Resta
  | Potencia
  | ParentesisOpen
  | ParentesisCierre
  | Real String
  | Asignacion
  | Variable String
  | Comentario String
  | Operador String
  | Multiplicacion

  deriving (Show)

type Nline = Int
type RVal = Either String [Token]

lexer :: String -> [Token]
lexer [] = []
lexer ('/':'/':cs) = [Comentario ('/':'/':cs)]
lexer (c:cs)
  | isDigit c || (c == '-' && not (null cs) && (isDigit (head cs) || head cs == '.')) = lexNoR (c:cs)
  | isLetter c || c == '_' = iDentif (c:cs)
  | c == '=' = Asignacion : lexer cs
  | elem c "+-*/^" = Operador [c] : lexer cs
  | c == '(' = ParentesisOpen : lexer cs
  | c == ')' = ParentesisCierre : lexer cs
  | otherwise = lexer cs

lexNoR :: String -> [Token]
lexNoR cs =
  let (num, rest) = span (\x -> isDigit x || x == '.' || x == 'E' || x == 'e' || x == '-') cs
   in if elem '.' num || elem 'E' num || elem 'e' num
      then Real num : lexer rest
      else Entero num : lexer rest

iDentif :: String -> [Token]
iDentif cs =
  let (ident, rest) = span (\x -> isDigit x || isLetter x || x == '_') cs
   in Variable ident : lexer rest

tkToSTR :: Token -> String
tkToSTR token = case token of
  ParentesisOpen -> "ParentesisAbre\t("
  ParentesisCierre -> "ParentesisCierra\t)"
  Entero n -> "Entero\t\t" ++ n
  Real n -> "Real\t\t" ++ n
  Asignacion -> "Asignacion\t="
  Variable ident -> "Variable\t" ++ ident
  Comentario c -> "Comentario\t" ++ c
  Multiplicacion -> "Multiplicacion\t*"
  Division -> "Division\t/"
  Suma -> "Suma\t\t+"
  Resta -> "Resta\t\t-"
  Potencia -> "Potencia\t^"
  Operador op -> "Operador\t" ++ op


tables :: [Token] -> String
tables tokens =
  let headers = "Tipo\tValor\n" ++ replicate 50 '-'
      rows = map tkToSTR tokens
   in headers ++ "\n" ++ intercalate "\n" rows

validLines :: [String] -> [(Nline, RVal)]
validLines lines = zipWith (\n line -> (n, lineToken (lexer line))) [1..] lines

lineToken :: [Token] -> RVal
lineToken tokens
  | null tokens = Left "Línea vacía"
  | not $ isParenthesesValid tokens 0 = Left "Paréntesis desbalanceados"
  | otherwise = Right tokens

isParenthesesValid :: [Token] -> Int -> Bool
isParenthesesValid [] 0 = True -- Caso base: no hay tokens y los paréntesis están balanceados
isParenthesesValid [] _ = False -- Caso base: no hay tokens pero los paréntesis no están balanceados
isParenthesesValid (t:ts) contador =
    case t of
        ParentesisOpen ->  isParenthesesValid ts (contador + 1)
        ParentesisCierre -> if contador <= 0 then False else isParenthesesValid ts (contador - 1)
        _ -> isParenthesesValid ts contador


logValidationResults :: [(Nline, RVal)] -> IO ()
logValidationResults results = mapM_ reportResult results
  where
    reportResult (lineNum, Right _) = putStrLn $ "Línea " ++ show lineNum ++ ": Válida"
    reportResult (lineNum, Left errorMsg) = putStrLn $ "Línea " ++ show lineNum ++ ": Error - " ++ errorMsg

recordValidData:: [(Nline, RVal)] -> IO ()
recordValidData results = do
  let validLines = map (\(lineNum, Right tokens) -> (lineNum, tokens)) $ filter (\(_, result) -> case result of { Right _ -> True; _ -> False }) results
  writeFile "output.txt" $ intercalate "\n" $ map (tables . snd) validLines -- Escribir las líneas válidas en output.txt



main :: IO ()
main = do
  contents <- readFile "input.txt"
  let linesOfContents = lines contents
  let validationResults = validLines linesOfContents
  logValidationResults validationResults
  let validTokens = [tokens | (_, Right tokens) <- validationResults]
  recordValidData validationResults


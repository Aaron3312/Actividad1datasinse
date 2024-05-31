import Data.Array.IO (writeArray)
import Data.Char (isDigit, isLetter, isSpace)
import Data.List (elem, intercalate)

data Token
  = Entero String
  | ParentesisOp
  | ParentesisCls
  | Real String
  | Asignacion
  | Variable String
  | Comentario String
  | Operador String
  deriving (Show)

type Nline = Int

type RVal = Either String [Token]

lexicalAnalyzer :: String -> [Token]
lexicalAnalyzer [] = []
lexicalAnalyzer ('/' : '/' : cs) = [Comentario ('/' : '/' : cs)]
lexicalAnalyzer (c : cs)
  | isDigit c || (c == '-' && not (null cs) && (isDigit (head cs) || head cs == '.')) = lexNoR (c : cs)
  | isLetter c || c == '_' = iDentif (c : cs)
  | c == '=' = Asignacion : lexicalAnalyzer cs
  | elem c "+-*/^" = Operador [c] : lexicalAnalyzer cs 
  | c == '(' = ParentesisOp : lexicalAnalyzer cs
  | c == ')' = ParentesisCls : lexicalAnalyzer cs
  | otherwise = lexicalAnalyzer cs

lexNoR :: String -> [Token]
lexNoR cs =
  let (num, rest) = span (\x -> isDigit x || x == '.' || x == 'E' || x == 'e' || x == '-') cs
   in if elem '.' num || elem 'E' num || elem 'e' num
        then Real num : lexicalAnalyzer rest
        else Entero num : lexicalAnalyzer rest

iDentif :: String -> [Token]
iDentif (c : cs) =
  let (ident, rest) = span isLetterOrDigit (c : cs)
   in Variable ident : lexicalAnalyzer rest
  where
    isLetterOrDigit x = isDigit x || isLetter x

tkToSTR :: Token -> String
tkToSTR token = case token of
  ParentesisOp -> "ParentesisAbre\t("
  ParentesisCls -> "ParentesisCierra\t)"
  Entero n -> "Entero\t\t" ++ n
  Real n -> "Real\t\t" ++ n
  Asignacion -> "Asignacion\t="
  Variable ident -> "Variable\t" ++ ident
  Comentario c -> "Comentario\t" ++ c
  Operador op -> "Operador\t" ++ op

tables :: [Token] -> String
tables tokens =
  let headers = "Tipo\tValor\n" ++ replicate 50 '-'
      rows = map tkToSTR tokens
   in headers ++ "\n" ++ intercalate "\n" rows

validLines :: [String] -> [(Nline, RVal)]
validLines lines = zipWith (\n line -> if isValidLineStart line then (n, lineToken (lexicalAnalyzer line)) else (n, Left "Error: Formato de línea inválido. Debe comenzar con una letra seguida opcionalmente por '='")) [1 ..] lines
  where
    isValidLineStart :: String -> Bool
    isValidLineStart s = case dropWhile isSpace s of
      [] -> False -- Línea vacía después de eliminar espacios iniciales
      (x : xs) -> isLetter x && (null xs || xs == "=" || startsWithEqual xs)
    -- Verifica que después de la letra inicial, la línea esté vacía, contenga solo un '=', o tenga '=' después de espacios opcionales

    startsWithEqual :: String -> Bool
    startsWithEqual s = case dropWhile isSpace s of
      ('=' : _) -> True
      _ -> False

lineToken :: [Token] -> RVal
lineToken tokens
  | null tokens = Left "Línea vacía"
  | not $ isParenthesesValid tokens 0 = Left "Paréntesis desbalanceados"
  | not $ isParenthesisPrecededByOperation tokens = Left "Cada paréntesis abierto debe ser precedido por una operación"
  | not $ parenthesesHaveContent tokens = Left "Los paréntesis deben contener algo dentro"
  | not $ areOperatorsValid tokens = Left "Todos los operadores deben tener operandos"
  | otherwise = Right tokens

isParenthesisPrecededByOperation :: [Token] -> Bool
isParenthesisPrecededByOperation [] = True -- Caso base: no hay tokens
isParenthesisPrecededByOperation (ParentesisOp : _) = False -- Caso base: el primer token es un paréntesis abierto
isParenthesisPrecededByOperation (ParentesisCls : _) = False -- Caso base: el primer token es un paréntesis cerrado
isParenthesisPrecededByOperation (Operador _ : ParentesisOp : _) = True -- Caso base: un operador es seguido por un paréntesis abierto
isParenthesisPrecededByOperation (Operador _ : ParentesisCls : _) = False -- Caso base: un operador es seguido por un paréntesis cerrado
isParenthesisPrecededByOperation (t : ts) = isParenthesisPrecededByOperation ts


isParenthesesValid :: [Token] -> Int -> Bool
isParenthesesValid [] 0 = True -- Caso base: no hay tokens y los paréntesis están balanceados
isParenthesesValid [] _ = False -- Caso base: no hay tokens pero los paréntesis no están balanceados
isParenthesesValid (t : ts) (2) = False -- Caso base: los paréntesis están desbalanceados
isParenthesesValid (t : ts) contador =
  case t of
    ParentesisOp -> isParenthesesValid ts (contador + 1)
    ParentesisCls -> if contador <= 0 then False else isParenthesesValid ts (contador - 1)
    _ -> isParenthesesValid ts contador

parenthesesHaveContent :: [Token] -> Bool
parenthesesHaveContent tokens = go tokens False where
  go [] _ = True
  go (ParentesisOp : rest) _ = case rest of
    ParentesisCls : _ -> False -- Encuentra un paréntesis vacío inmediatamente
    _ -> go rest True -- Se encontró un ParentesisOp, esperando contenido
  go (ParentesisCls : rest) hadContent = if hadContent then go rest False else False -- Verifica que haya habido contenido
  go (_ : rest) hadContent = go rest hadContent -- Continúa con el resto de los tokens

    

areOperatorsValid :: [Token] -> Bool
areOperatorsValid tokens = all isValidOperatorPosition [0..length tokens - 1]
  where
    isValidOperatorPosition i = case tokens !! i of
      Operador _ -> (i > 0 && isOperand (tokens !! (i - 1))) && (i < length tokens - 1 && isOperand (tokens !! (i + 1)))
      _ -> True
    isOperand (Entero _) = True
    isOperand (Real _) = True
    isOperand (Variable _) = True
    isOperand ParentesisOp = True
    isOperand ParentesisCls = True
    isOperand _ = False

logValidationResults :: [(Nline, RVal)] -> IO ()
logValidationResults results = mapM_ reportResult results
  where
    reportResult (lineNum, Right _) = putStrLn $ "Token " ++ show lineNum ++ ": OK"
    reportResult (lineNum, Left errorMsg) = putStrLn $ "Token " ++ show lineNum ++ ": Error" ++ errorMsg

recordValidData :: [(Nline, RVal)] -> IO ()
recordValidData results = do
  let validLines = map (\(lineNum, Right tokens) -> (lineNum, tokens)) $ filter (\(_, result) -> case result of Right _ -> True; _ -> False) results
  writeFile "output.txt" $ intercalate "\n" $ map (tables . snd) validLines -- Escribir las líneas válidas en output.txt

main :: IO ()
main = do
  contents <- readFile "input.txt"
  let linesOfContents = lines contents
  let validationResults = validLines linesOfContents
  logValidationResults validationResults
  let validTokens = [tokens | (_, Right tokens) <- validationResults]
  recordValidData validationResults

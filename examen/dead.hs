import Data.Char (isDigit, isLetter)

data Expr
  = Var String
  | IntLit Integer
  | Plus Expr Expr
  | Minus Expr Expr
  | Times Expr Expr
  | Divide Expr Expr

data Token -- Añadido token para manejar números enteros, reales, identificadores, comentarios, operadores y paréntesis
  = TInt String -- Añadido token para números enteros
  | TReal String -- Añadido token para números reales
  | TAssign -- Añadido token para el operador de asignación
  | TVar String -- Añadido token para identificadores
  | TComment String -- Añadido token para comentarios
  | TOp String -- Añadido token para operadores
  | TLParenOpen -- Añadido token para el paréntesis izquierdo
  | TLParenClose -- Añadido token para el paréntesis derecho
  deriving (Show)

-- Añadido función para manejar el lexer
lexer :: String -> [Token]
lexer [] = []
lexer ('/':'/':cs) = [TComment ('/':'/':cs)] -- Maneja comentarios
lexer (c : cs)
  | isDigit c = lexNumberOrReal (c : cs) -- Añadido manejo de números
  | isLetter c = lexIdentifier (c : cs) -- Añadido manejo de identificadores
  | c == '=' = TAssign : lexer cs -- Añadido manejo del operador de asignación
  | c == '+' = TOp "+" : lexer cs -- Añadido manejo del operador de suma
  | c == '-' = TOp "-" : lexer cs -- Añadido manejo del operador de resta
  | c == '/' = TOp "/" : lexer cs -- Añadido manejo del operador de división
  | c == '*' = TOp "*" : lexer cs -- Añadido manejo del operador de multiplicación
  | c == '(' = TLParenOpen : lexer cs -- Añadido manejo del paréntesis izquierdo
  | c == ')' = TLParenClose : lexer cs -- Añadido manejo del paréntesis derecho
  | otherwise = lexer cs

-- Añadido función para manejar números
lexNumberOrReal :: String -> [Token]
lexNumberOrReal cs =
  let (num, rest) = span (\x -> isDigit x || x == '.' || x == 'E' || x == 'e' || x == '-') cs
   in if 'E' `elem` num || 'e' `elem` num || '.' `elem` num
        then TReal num : lexer rest
        else TInt num : lexer rest

-- Añadido función para manejar identificadores
lexIdentifier :: String -> [Token]
lexIdentifier cs =
  let (ident, rest) = span (\x -> isDigit x || isLetter x) cs
   in TVar ident : lexer rest

-- Función para probar el lexer con un archivo
main :: IO ()
main = do
  putStrLn "Lexer"
  contents <- readFile "input.txt"
  let tokens = concatMap lexer (lines contents) 
  print tokens
  writeFile "output.txt" (show tokens)
  putStrLn "Fin"

import Data.Char (isDigit, isLetter)

data Expr
  = Var String
  | IntLit Integer
  | Plus Expr Expr
  | Minus Expr Expr
  | Times Expr Expr
  | Divide Expr Expr

data Token
  = TInt String
  | TReal String
  | TAssign
  | TVar String
  | TComment String
  | TOp String
  deriving (Show)

lexer :: String -> [Token]
lexer [] = []
lexer (c:cs)
  | isDigit c = lexNumberOrReal (c:cs)
  | isLetter c = lexIdentifier (c:cs)
  | c == '=' = TAssign : lexer cs
  | c == '+' = TOp "+" : lexer cs
  | c == '-' = TOp "-" : lexer cs
  | c == '/' && not (null cs) && head cs == '/' = [TComment (c:cs)]
  | otherwise = lexer cs

lexNumberOrReal :: String -> [Token]
lexNumberOrReal cs =
  let (num, rest) = span (\x -> isDigit x || x == '.' || x == 'E' || x == 'e' || x == '-') cs
  in if 'E' `elem` num || 'e' `elem` num || '.' `elem` num
     then TReal num : lexer rest
     else TInt num : lexer rest

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

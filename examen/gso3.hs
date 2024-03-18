import Data.Char (isDigit, isLetter)
import Control.Concurrent (writeChan)
import Language.Haskell.TH.PprLib (comma)
import Control.Monad.Trans.Accum (evalAccum)

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
  | Texponential String
  deriving (Show)

lexer :: String -> [Token]
lexer [] = []
lexer (c : cs)
  | isDigit c = lexNumber (c : cs)
  | c == 'E' = lexExpIdentifier (c : cs)
  | isLetter c = lexIdentifier (c : cs) 
  | c == '=' = TAssign : lexer cs
  | c == '+' = TOp "+" : lexer cs
  | c == '-' = TOp "-" : lexer cs
  | c == '/' && not (null cs) && head cs == '/' = [TComment (c : cs)]
  | otherwise = lexer cs

lexNumber :: String -> [Token]
lexNumber cs = let (number, rest) = span isDigit cs in TInt number : lexer rest

lexIdentifier :: String -> [Token]
lexIdentifier cs =
  let (ident, rest) = span (\x -> isDigit x || isLetter x && x /= 'E') cs
   in TVar ident : lexer rest

lexExpIdentifier :: String -> [Token]
lexExpIdentifier cs = --definimos 45E-2 cuando tenga E
  let (ident, rest) = span (\x -> isDigit x || isLetter x) cs
    in Texponential ident : lexer rest


-- Función para probar el lexer con un archivo
main :: IO ()
main = do
  print "Lexer"
  contents <- readFile "input.txt"
  let tokens = concatMap lexer (lines contents)
  print tokens
  
  writeFile "output.txt" (show tokens)
  print "Fin"
  -- print evaluation
  print "Evaluation"
  
  
  -- print "Parser"




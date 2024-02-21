import Control.Monad.RWS (MonadState(put))
import Text.Read (Lexeme(String))

-- a)	Exercise: Implement a Function to Reverse a List Problem Statement:
-- Write a Haskell function that reverses a list without mutating the original list.
-- Requirements:
-- ▪	The function should take a list of elements as input.
-- ▪	It should return a new list with the elements in reverse order.
-- ▪	The original list should remain unchanged; no mutation of the list is allowed.

reverseList :: [a] -> [a]
reverseList [] = []
reverseList (x : xs) = reverseList xs ++ [x]

-- Solution: This is a simple program that reverses a list without mutating the original list.
main :: IO ()
main = do
    putStrLn "Enter a list"
    list <- getLine
    let list1 = read list :: [String]
    putStrLn ("The list is " ++ show list1)
    putStrLn ("The list reversed is " ++ show (reverseList list1))
    putStrLn ("The original list is " ++ show list1)
  


-- Call to print the input and output:
-- reverseList [1,2,3,4,5]
-- [5,4,3,2,1]
-- reverseList [5,4,3,2,1]
-- [1,2,3,4,5]

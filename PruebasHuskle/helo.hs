import Text.XHtml (p)
-- This is a comment
--2.	Practice some basics in Haskell to demonstrate functional programming characteristics. Include your source code in the same file or corresponding problem, each functions or line of code must include a comment or brief description on what it does, also it should include solution and call to print the input and output. 

main :: IO ()
main = do
    putStrLn "Hello, what is your name?"
    name <- getLine
    putStrLn ("Hello, " ++ name ++ ", how are you?")
-- Solution: This is a simple program that asks for the user's name and then greets the user.
-- Call to print the input and output:
-- Hello, what is your name?
-- John
-- Hello, John, how are you?

-- practice 2

    putStrLn "Enter a number"
    num <- getLine
    let number = read num :: Int
    putStrLn ("The number is " ++ show number)
-- Solution: This is a simple program that asks for a number and then prints the number.

-- Call to print the input and output:
-- Enter a number
-- 5
-- The number is 5

-- practice 3

    putStrLn "Enter a number"
    num1 <- getLine
    let number1 = read num1 :: Int
    putStrLn "Enter another number"
    num2 <- getLine
    let number2 = read num2 :: Int
    putStrLn ("The sum of the numbers is " ++ show (number1 + number2))
-- Solution: This is a simple program that asks for two numbers and then prints the sum of the numbers.

-- Call to print the input and output:
-- Enter a number
-- 5
-- Enter another number
-- 3
-- The sum of the numbers is 8


-- practice 4

    putStrLn "Enter a number"
    num3 <- getLine
    let number3 = read num3 :: Int
    putStrLn ("The number is " ++ show number3)
    putStrLn ("The number squared is " ++ show (number3 * number3))
-- Solution: This is a simple program that asks for a number and then prints the number and the square of the number.

-- Call to print the input and output:
-- Enter a number
-- 5
-- The number is 5
-- The number squared is 25

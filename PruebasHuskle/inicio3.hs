factorial :: Integer -> Integer
factorial 0 = 1
factorial n = n * factorial (n - 1)

main :: IO ()
main = do
    let input = 5
    putStrLn $ "Factorial of " ++ show input ++ " is: " ++ show (factorial input)

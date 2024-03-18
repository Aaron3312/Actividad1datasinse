import Text.XHtml (p)
applyTwice :: (a -> a) -> a -> a
applyTwice f x = f (f x)

double :: Int -> Int
double x = x * 2



main :: IO ()
main = do
    putStrLn $ "Result 1: " ++ show (applyTwice (*2) 3)
    putStrLn $ "Result 1: " ++ show (applyTwice double 5)
    putStrLn $ "Result 2: " ++ show (applyTwice reverse "Haskell")
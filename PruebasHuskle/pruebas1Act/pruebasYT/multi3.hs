-- Aaron Hernandez Jimenez A01642529
-- Jesus Enrique Bañales Lopez A01642425

-- hacer una funcion recurciva que imprima un mensaje infinitamente
funcionRecursiva :: Int -> IO ()
funcionRecursiva x = do
  putStrLn "Hola"
  funcionRecursiva x

multi2 :: Int -> Int
multi2 x = x ^ 2

funcionSuma :: Int -> Int -> Int
funcionSuma x y = (multi2 (x)) + (multi2 (y))

funcionCayDoble :: Int -> Int
funcionCayDoble x = funcionSuma (x - 1) (x + 1)

multi3 :: Int -> Int
multi3 x = x * 3

main = do
  putStrLn "Enter a number"
  list <- getLine
  let list1 = read list :: Int
  putStrLn ("The number is " ++ show list1)
  putStrLn ("The number multiplied by 3 is " ++ show (multi3 list1))
  putStrLn ("The number multiplied al cubo is " ++ show (multi2 list1))
  putStrLn ("The number multiplied by 2^x-1 + 2^x+1 is " ++ show (funcionCayDoble list1))
  funcionRecursiva list1
-- Date: 2020 11 10
pruebas1 :: Int -> Int -> Int
pruebas1 x y = x + y

isPositive :: Int -> String 
isPositive x = if x >= 0
                then "Positive"
                else "Negative"

positives   :: [Int] -> [Int]
positives [] = []
positives (x:xs) = if x >= 0 then x : positives xs else positives xs


main = do
  print ("Hola mundo")
  print (pruebas1 5 3)
  print (isPositive (-4))
  let f = [32, -34, -35, 36, -37, 38, -39, 40, 41, 42]
  print (f!!2)
  print (positives f!!2)
  let num = [-100..100]
  print (positives num)





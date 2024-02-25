import Control.Monad.RWS (MonadState (put))
import Distribution.Utils.Structured (Structure (Structure))
import GHC.IO.Device (IODevice (dup))

-- Aaron Hernandez Jimenez A01642529, Act 5.2
-- to run this in ghci use this  :l Act5.2.hs

farenheit_celsius :: Float -> Float
farenheit_celsius f = ((f - 32) * 5) / 9

sing :: Int -> Int
sing n = if n == 0 then 0 else if n > 0 then 1 else -1

roots :: Float -> Float -> Float -> (Float, Float)
roots a b c = ((-b + sqrt (b ^ 2 - 4 * a * c)) / (2 * a), (-b - sqrt (b ^ 2 - 4 * a * c)) / (2 * a))

iDMC :: Float -> Float -> String
iDMC x y = if (x / (y ^ 2)) < 20 then "Underweight" else if (x / (y ^ 2)) >= 20 && (x / (y ^ 2)) < 25 then "Normal weight" else if (x / (y ^ 2)) >= 25 && (x / (y ^ 2)) < 30 then "obese 1" else if (x / (y ^ 2)) >= 30 && (x / (y ^ 2)) < 40 then "obese 2" else "obese 3"

numeroLargo :: Int
numeroLargo = 0

factorial :: Integer -> Integer
factorial n = if n == 0 then 1 else n * factorial (n - 1)

duplicate :: [a] -> [a]
duplicate = concatMap (\x -> [x, x])

pow :: Int -> Int -> Int
pow a b = if b == 0 then 1 else a ^ b

-- hay forma de usar la recursion para hacer la funcion pow
-- pow :: Int -> Int -> Int
-- pow a b = if b == 0 then 1 else a * pow a (b-1)
-- no la entiendo al 100

-- definimos a = 1 y b = 1
fib :: Int -> Int

a = 1

b = 1

fib 0 = a
fib 1 = b
fib 2 = 1
fib 3 = 2
fib 4 = 3
fib 5 = 5
fib 6 = 8
fib 7 = 13
fib 8 = 21
fib 9 = 34
fib 10 = 55
fib 11 = 89
fib 12 = 144
fib 13 = 233
fib 14 = 377
fib 15 = 610
fib 16 = 987
fib 17 = 1597
fib 18 = 2584
fib 19 = 4181
fib 20 = 6765
fib 21 = 10946
fib 22 = 17711
-- precargue algunos para facilitar la prueba
fib n = fib (n - 1) + fib (n - 2)

-- guardamos la informacion que genera cada que buscamos un numero de la secuencia de fibonacci

main = do
  -- funcion farenheit_celsius
  -- lo que hace esta funcion es convertir de farenheit a celsius
  -- se le pide al usuario que ingrese un numero y se le muestra el resultado

  putStrLn "Enter a temperature in Farenheit"
  f <- getLine
  let f1 = read f :: Float
  putStrLn ("The temperature in Celsius is " ++ show (farenheit_celsius f1))
  -- funcion sing
  -- lo que hace esta funcion es determinar el signo de un numero
  -- se le pide al usuario que ingrese un numero y se le muestra el resultado
  putStrLn "Enter a number"
  n <- getLine
  let n1 = read n :: Int
  putStrLn ("The number is " ++ show n1)
  putStrLn ("The sign of the number is " ++ show (sing n1))
  -- funcion roots
  -- lo que hace esta funcion es calcular las raices de una ecuacion cuadratica
  -- se le pide al usuario que ingrese los valores de a, b y c y se le muestra el resultado
  putStrLn "Enter the value of a"
  a <- getLine
  let a1 = read a :: Float
  putStrLn "Enter the value of b"
  b <- getLine
  let b1 = read b :: Float
  putStrLn "Enter the value of c"
  c <- getLine
  let c1 = read c :: Float
  putStrLn ("The roots of the equation are " ++ show (roots a1 b1 c1))

  -- funcion IDMC
  -- lo que hace esta funcion es calcular el indice de masa corporal
  -- se le pide al usuario que ingrese los valores de peso y altura y se le muestra el resultado
  putStrLn "Enter the value of height"
  y <- getLine
  let y1 = read y :: Float
  putStrLn "Enter the value of weight"
  x <- getLine
  let x1 = read x :: Float
  putStrLn ("The IDMC is " ++ show (iDMC x1 y1))

  -- funcion Factorial
  -- lo que hace esta funcion es calcular el factorial de un numero
  -- se le pide al usuario que ingrese un numero y se le muestra el resultado
  putStrLn "Enter a number"
  n <- getLine
  let n1 = read n :: Integer
  putStrLn ("The factorial of the number is " ++ show (factorial n1))

  -- funcion duplicate
  -- lo que hace esta funcion es tomar una lista como entrada y devolver una lista con los elementos duplicados
  -- se le pide al usuario que ingrese una lista y se le muestra el resultado
  putStrLn "Enter a list of numbers or characters separated by commas"
  list <- getLine
  let list1 = read list :: [Int]
  putStrLn ("The list with the elements duplicated is " ++ show (duplicate list1))

  -- Funcion Pow La funcion pow toma dos entradas como entrada: un numero a y un entero positivo b. devuelve el resultado
  -- de calcular a elevado a la potencia b.
  -- se le pide al usuario que ingrese un numero y un entero positivo y se le muestra el resultado
  putStrLn "Enter a number"
  a <- getLine
  let a1 = read a :: Int
  putStrLn "Enter a positive integer"
  b <- getLine
  let b1 = read b :: Int
  putStrLn ("The result of " ++ show a1 ++ " to the power of " ++ show b1 ++ " is " ++ show (pow a1 b1))

  -- funcionFIB toma un entero positivo n como entrada y devuelve el elemento correspoondiente de la secuencia de Fibonacci
  -- se le pide al usuario que ingrese un numero y se le muestra el resultado

  putStrLn "Enter a number"
  n <- getLine
  let n1 = read n :: Int
  putStrLn ("The number is " ++ show n1)
  putStrLn ("The number in the Fibonacci sequence is " ++ show (fib n1))

  return ()

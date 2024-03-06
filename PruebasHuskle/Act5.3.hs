import Language.Haskell.TH (Lit (IntegerL))

-- Aaron Hernandez Jimenez A01642529
-- actividad 5.3

-- Ejercicio 1
-- la funcion positives toma un alista de numeros lst como entrada y regresa una nueva lista que solo contiene numeros positivos de lst

positives :: [Int] -> [Int]
positives [] = []
positives (x : xs) = if x > 0 then x : positives xs else positives xs

-- si la lista esta vacia regresa una lista vacia
-- si la lista no esta vacia, compara el primer elemento de la lista con 0, si es mayor a 0 lo agrega a la lista y llama a la funcion con el resto de la lista

-- x es la cabeza y xs es la cola

-- Ejercicio 2
-- son iguales jaajaj literalmente es la misma funcion positives

-- Ejercicio 3
-- la funcion add-list devuelve la suma de los numeros contenidos en la lista que recibe como entrada, 0 si esta vacia

addList :: [Int] -> Int
addList [] = 0
addList (x : xs) = x + addList xs

-- Ejercicio 4
-- la funcion invertPairs toma como entrada una lista cuyo contenido son listas de dos elementos
-- y regresa una lista con cada pareja invertida

invertPairs :: [[a]] -> [[a]]
invertPairs [] = []
invertPairs (x : xs) = reverse x : invertPairs xs

-- Ejercicio 5
-- la funcion listOfSymbols toma una lista como entrada y devuelve verdadero si todos los elementos de la lista son simbolos,
-- falso en otro caso

listOfSymbols [] = True
listOfSymbols (x : xs) = if x == x then listOfSymbols xs else False

-- Ejercicio 6
-- la funcion swapper toma tres entradas: dos valores a y b y una lista lst. devuelve una nueva lista
-- en la cual cada ocurrencia de a en lst se intercambia por b y viceversa. cualquier otro elemento de lst permanece igual
-- se puede suponer que list no coniene listas anidadas

swapper a b [] = []
swapper a b (x : xs) = if x == a then b : swapper a b xs else if x == b then a : swapper a b xs else x : swapper a b xs

-- Ejercicio 7
-- la funcion dot-product toma dos entradas las listas a y b, devuelve el resultado de realizar el producto punto de a por b

dotProduct :: [Float] -> [Float] -> Float
dotProduct [] [] = 0
dotProduct (x : xs) (y : ys) = x * y + dotProduct xs ys

-- Ejercicio 8
-- la funcion average recibe una lista de numeros lst como entrada, devuelve la media aritmetica de los elemtos
-- de lst o 0 si esta vacia

average :: [Float] -> Float
average [] = 0
average lst = sum lst / fromIntegral (length lst)

-- Ejercicio 9
-- la funcion standardDeviation recibe una lista como entrada y devuelvve la desviacion estandar de los elementos de la lista
-- o 0 si esta vacia la desviacion estandar de poblacion

standardDeviation :: [Float] -> Float
standardDeviation lst = sqrt (sum [(x - avg) ^ 2 | x <- lst]) / fromIntegral (length lst)
    where avg = average lst

-- Ejercicio 10
-- la funcion replic toma 2 entradas una lista y otra un numero entero n, donde n>= 0
-- devuelve una nueva lista que replica n vecces cada elemento de list

replic :: Int -> [a] -> [a]
replic _ [] = []
replic 0 _ = []
replic n (x : xs) = replicate n x ++ replic n xs

-- Ejercicio 11
-- la funcion expand toma una lista como entrada y devuelve una lsita donde el primer elemento de
-- la lista aparece una vez, el segundo aparece 2 veces y el tercero aparece 3 veces y asi sucesivamente

expand :: [Int] -> [Int]
expand xs = concat [replicate i x | (i, x) <- zip [1 ..] xs]



main = do
  print (positives [1, 2, -3, 4, 5, -6, 7, 8, 9, 10])
  print (addList [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
  print (invertPairs [[1, 2], [3, 4], [5, 6], [7, 8], [9, 10]])
  print (reverse [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
  print (listOfSymbols ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'])
  print (swapper 1 3 [1, 3, 2])
  print (dotProduct [1, 2, 3] [4, 5, 6])
  print (average [5,6,1,6,0,1,2])
  print (standardDeviation [4, 8, 15, 16, 23, 42])
  print (replic 4 [1,2,3,4])
  print (expand [1,2,3,4])

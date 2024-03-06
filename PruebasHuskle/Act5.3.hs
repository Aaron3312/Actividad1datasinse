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
--son iguales jaajaj literalmente es la misma funcion positives

-- Ejercicio 3
-- la funcion add-list devuelve la suma de los numeros contenidos en la lista que recibe como entrada, 0 si esta vacia

addList :: [Int] -> Int
addList [] = 0
addList (x : xs) = x + addList xs

-- Ejercicio 4
-- la funcion invertPairs toma como entrada una lista cuyo contenido son listas de dos elementos 
-- y regresa una lista con los elementos de las listas originales intercambiados 




main = do
  print (positives [1, 2, -3, 4, 5, -6, 7, 8, 9, 10])
  print (addList [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])



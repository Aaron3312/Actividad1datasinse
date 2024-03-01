import Data.List (delete)
import Language.Haskell.TH (Strict)

-- un programa que identifique anagramas 5.4
-- Aaron Hernandez Jimenez A01642529
-- si es igual no hay anagrama 

verifyThatsNotEqual :: String -> String -> String
verifyThatsNotEqual [] [] = "No es anagrama"
verifyThatsNotEqual [] _ = "No es anagrama"
verifyThatsNotEqual _ [] = "No es anagrama"
verifyThatsNotEqual (x:xs) (y:ys) = if x == y then "no es anagrama" else anagram (x:xs) (y:ys)


anagram :: String -> String -> String
anagram [] [] = "es anagrama"
anagram [] _ = "no es anagrama"
anagram _ [] = "no es anagrama"
anagram (x:xs) ys = anagram xs (delete x ys)


numDia d m a =
    (d + floor(fromIntegral(13*(m'+1))/5) + a' + floor(fromIntegral a'/4) + floor(fromIntegral j/4) - 2*j) `mod` 7
  where
    (m', a') = if m < 3 then (m + 12, a - 1) else (m, a)
    j = floor(fromIntegral a' / 100)

diaSemana a m d = do
    let resultado =  (numDia d m a)
    if resultado == 0
        then putStrLn "Naciste un Viernes."
    else if resultado == 1
        then putStrLn "Naciste un Sabado."
    else if resultado == 2
        then putStrLn "Naciste un Domingo."
    else if resultado == 3
        then putStrLn "Naciste un Lunes."
    else if resultado == 4
        then putStrLn "Naciste un Martes."
    else if resultado == 5
        then putStrLn "Naciste un Miercoles."
    else if resultado == 6
        then putStrLn "Naciste un Jueves."
    else
        putStrLn "No naciste."


-- una funcion caracol que recibe el caracol esta en un poso de longitud l, sube s metros cada dia
-- y se resbala R metros, dados esos calcular los dias en lo que tarda en ssubir el pozo
caracol :: Int -> Int -> Int -> Int
caracol l s r = if s > l then 1 else if s == l then 1 else if s < l then caracol(l - s + r) s r + 1 else caracol (l - s + r) s r + 1


main :: IO ()
main = do
  print (verifyThatsNotEqual "hola" "aloha")
  print (verifyThatsNotEqual "hola" "koka")
  print (verifyThatsNotEqual "hola" "hola")
  print (verifyThatsNotEqual "hola" "aloh")
  putStrLn "Ingrese la palabra 1 del anagrama:"
  p <- readLn
  putStrLn "Ingrese la palabra 2 del anagrama:"
  ps <- readLn
  print (verifyThatsNotEqual p ps)

    
  putStrLn "Ingrese su año de nacimiento:"
  a <- readLn
  putStrLn "Ingrese su mes de nacimiento:"
  m <- readLn
  putStrLn "Ingrese su día de nacimiento:"
  d <- readLn
  diaSemana a m d


  print ("el caracol en un pozo de l 10 y sube s 3 metros y se resbala R 2 por lo tanto sube en: " ++ show (caracol 10 3 2) ++ " dias" )
  print ("el caracol en un pozo de l 1 y sube s 3 metros y se resbala R 2 por lo tanto sube en: " ++ show (caracol 1 3 2) ++ " dias" )
  print ("el caracol en un pozo de l 4 y sube s 3 metros y se resbala R 2 por lo tanto sube en: " ++ show (caracol 4 3 2) ++ " dias" )
  print ("el caracol en un pozo de l 6 y sube s 2 metros y se resbala R 1 por lo tanto sube en: " ++ show (caracol 6 2 1) ++ " dias" )

  putStrLn "Ingrese la longitud del pozo:"
  l <- readLn
  putStrLn "Ingrese lo que sube el caracol:"
  s <- readLn
  putStrLn "Ingrese lo que retrocesa:"
  r <- readLn
  print ("el caracol en un pozo de l 6 y sube s 2 metros y se resbala R 1 por lo tanto sube en: " ++ show (caracol l s r) ++ " dias" )




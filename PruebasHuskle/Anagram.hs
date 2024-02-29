--un programa que identifique anagramas 5.4


anagram :: String -> String -> Bool
anagram [] [] = True
anagram [] _ = False
anagram _ [] = False
anagram (x:xs) ys = anagram xs (delete x ys)
    where delete x [] = []
          delete x (y:ys) = if x == y then ys else y : delete x ys

main = do
    print (anagram "hola" "aloh")
    print (anagram "hola" "aloha")




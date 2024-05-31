import Data.IORef
import Control.Monad (when)

-- Declaración de un array
arrayParesEs :: [(String, String)]
arrayParesEs = 
    [ ("S", "Programa{")
    , ("V", "a")
    , ("Igual", "=")
    , ("E", "4")
    , ("S", "+")
    , ("E", "5")
    , ("D", "Real")
    , ("V", "b")
    , ("Igual", "=")
    , ("Rl", "5E-8")
    , ("V", "serie")
    , ("Igual", "=")
    , ("PA", "(")
    , ("V", "a")
    , ("Multi", "*")
    , ("V", "b")
    , ("S", "+")
    , ("E", "9")
    , ("PC", ")")
    , ("End", "}}")
    ]

-- Acceso a los valores del array
primerValor :: Int -> String
primerValor n = fst (arrayParesEs !! n)

segundoValor :: Int -> String
segundoValor n = snd (arrayParesEs !! n)

-- Definición de la función while
while :: IO Bool -> IO () -> IO ()
while cond action = do
    c <- cond
    when c $ do
        action
        while cond action

-- Función Renglon
renglon :: IORef Int -> IO ()
renglon nRef = do
    i <- readIORef nRef
    if i >= length arrayParesEs
        then return ()
        else do
            if primerValor i == "C"
                then do
                    putStr (segundoValor i)
                    putStrLn ""
                else do
                    when (primerValor i == "PA") $ do
                        putStr (segundoValor i ++ " | ")
                        let newQ = i + 1
                        writeIORef nRef newQ
                    i <- readIORef nRef
                    when (primerValor i == "E" || primerValor i == "Rl" || primerValor i == "V") $ do
                        putStr (segundoValor i)
                        when (i + 1 < length arrayParesEs && primerValor (i + 1) == "PC") $ do
                            let newQ = i + 1
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            putStr (" | " ++ segundoValor newQ)
                    i <- readIORef nRef
                    if i + 1 < length arrayParesEs && primerValor (i+1) /= "E" && primerValor (i+1) /= "Rl" && primerValor (i+1) /= "V" && primerValor (i+1) /= "Comentario" && primerValor (i+1) /= "PA" && primerValor (i+1) /= "PC" && primerValor (i+1) /= "D" && primerValor (i+1) /= "End"
                        then do
                            let newQ = i + 2
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            putStr (" | " ++ segundoValor (newQ-1) ++ " | ")
                            renglon nRef
                        else if i + 1 < length arrayParesEs && primerValor(i+1) == "Comentario"
                            then do
                                let newQ = i + 1
                                writeIORef nRef newQ
                                putStrLn (" | " ++ segundoValor newQ)
                            else do
                                putStrLn ""
                                return ()

-- Función arbol que imprime algunos valores y luego ejecuta el bucle while
arbol :: IO ()
arbol = do
    putStr "S -> "
    putStrLn (segundoValor 0)
    putStr "      programa{"
    putStrLn " RF"
    putStrLn ""
    
    ref <- newIORef ""
    n <- newIORef 1
    let condition = do
            num <- readIORef n
            return (primerValor num /= "End")
    let action = do
            num <- readIORef n
            if primerValor num /= "Comentario"
                then do
                    putStr "            R -> TV=O RF |->"
                    if primerValor num == "D"
                        then do
                            putStr ("T -> " ++ segundoValor num ++ " | " )
                            writeIORef n (num + 1)
                        else putStr "T -> eps | "
                    num <- readIORef n
                    putStr ("V -> " ++ segundoValor num ++ " | = | ")
                    writeIORef n (num + 2)
                    num <- readIORef n
                    putStr "O -> "
                    renglon n
                    num <- readIORef n
                    writeIORef n (num + 1)
                    putStr ""
                else putStrLn ("R -> "++ segundoValor num)
    while condition action
    putStrLn ""
    putStrLn "F -> }}"
    putStrLn "¡Proceso completado!"

-- Función principal del programa
main :: IO ()
main = do
    arbol
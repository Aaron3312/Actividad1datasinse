import Data.IORef
import Control.Monad (when)

-- Declaración de un array
arrayParesEnteros :: [(String, String)]
arrayParesEnteros = 
    [ ("Inicio", "Programa{principal{")
    , ("Variable", "a")
    , ("Igual", "=")
    , ("Entero", "4")
    , ("Suma", "+")
    , ("Entero", "5")
    , ("Tipo", "Real")
    , ("Variable", "b")
    , ("Igual", "=")
    , ("Real", "5E-8")
    , ("Variable", "serie")
    , ("Igual", "=")
    , ("ParentesisAbre", "(")
    , ("Variable", "a")
    , ("Multi", "*")
    , ("Variable", "b")
    , ("Suma", "+")
    , ("Entero", "9")
    , ("ParentesisCierra", ")")
    , ("Final", "}}")
    ]

-- Acceso a los valores del array
primerValor :: Int -> String
primerValor n = fst (arrayParesEnteros !! n)

segundoValor :: Int -> String
segundoValor n = snd (arrayParesEnteros !! n)

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
    if i >= length arrayParesEnteros
        then return ()
        else do
            if primerValor i == "Comentario"
                then do
                    putStr (segundoValor i)
                    putStrLn ""
                else do
                    when (primerValor i == "ParentesisAbre") $ do
                        putStr (segundoValor i ++ " | ")
                        let newQ = i + 1
                        writeIORef nRef newQ
                    i <- readIORef nRef
                    when (primerValor i == "Entero" || primerValor i == "Real" || primerValor i == "Variable") $ do
                        putStr (segundoValor i)
                        when (i + 1 < length arrayParesEnteros && primerValor (i + 1) == "ParentesisCierra") $ do
                            let newQ = i + 1
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            putStr (" | " ++ segundoValor newQ)
                    i <- readIORef nRef
                    if i + 1 < length arrayParesEnteros && primerValor (i+1) /= "Entero" && primerValor (i+1) /= "Real" && primerValor (i+1) /= "Variable" && primerValor (i+1) /= "Comentario" && primerValor (i+1) /= "ParentesisAbre" && primerValor (i+1) /= "ParentesisCierra" && primerValor (i+1) /= "Tipo" && primerValor (i+1) /= "Final"
                        then do
                            let newQ = i + 2
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            putStr (" | " ++ segundoValor (newQ-1) ++ " | ")
                            renglon nRef
                        else if i + 1 < length arrayParesEnteros && primerValor(i+1) == "Comentario"
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
    putStr (segundoValor 0)
    putStrLn " RF"
    
    ref <- newIORef ""
    n <- newIORef 1
    let condition = do
            num <- readIORef n
            return (primerValor num /= "Final")
    let action = do
            num <- readIORef n
            if primerValor num /= "Comentario"
                then do
                    putStrLn "R -> TV=O RF"
                    if primerValor num == "Tipo"
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
                else print "a"
    while condition action
    putStrLn "F -> }}"
    putStrLn "¡Proceso completado!"

-- Función principal del programa
main :: IO ()
main = do
    arbol
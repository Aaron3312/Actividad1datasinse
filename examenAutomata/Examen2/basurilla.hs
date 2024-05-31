

import Data.Tree
import Distribution.Simple.Build (build)

import Data.IORef
import Control.Monad (when)
import Control.Monad.RWS (MonadState (put)) 
import Data.Char (isDigit, isLetter, isSpace, isUpper, toLower, toUpper) 
import Data.List (find, intercalate, isPrefixOf, isSuffixOf) 
import System.IO
import Data.Text.Array (new)


-- Acceso a los valores del array
primerValor :: Int -> [(String, String)] -> String
primerValor n lista = fst (lista !! n)

-- Modificar la función segundoValor para aceptar una lista de pares (String, String)
segundoValor :: Int -> [(String, String)] -> String
segundoValor n lista = snd (lista !! n)

-- Definición de la función while
while :: IO Bool -> IO () -> IO ()
while cond action = do
    c <- cond
    when c $ do
        action
        while cond action

-- Función Renglon
-- Función renglón para procesar y mostrar información basada en la lista de pares
renglon :: IORef Int -> [(String, String)] -> IO ()
renglon nRef arrayParesEs = do
    i <- readIORef nRef
    if i >= length arrayParesEs
    then return ()
    else do
        let primer = primerValor i arrayParesEs
        let segundo = segundoValor i arrayParesEs
        if primer == "C"
        then do
            putStrLn segundo
            incrementarYContinuar nRef arrayParesEs
        else if primer == "PA"
        then do
            putStr (segundo ++ " | ")
            incrementarYContinuar nRef arrayParesEs
        else if primer == "E" || primer == "Rl" || primer == "V"
        then do
            putStr segundo
            handlePostCondicion nRef arrayParesEs i
        else if primer == "Comentario"
        then do
            putStrLn (" | " ++ segundo)
            incrementarYContinuar nRef arrayParesEs
        else putStrLn ""

-- Maneja la condición posterior si hay más elementos en la lista
handlePostCondicion :: IORef Int -> [(String, String)] -> Int -> IO ()
handlePostCondicion nRef arrayParesEs i = do
    if i + 1 < length arrayParesEs && primerValor (i + 1) arrayParesEs == "PC"
    then do
        modifyIORef nRef (+1)
        nuevoI <- readIORef nRef
        putStr (" | " ++ segundoValor nuevoI arrayParesEs)
        incrementarYContinuar nRef arrayParesEs
    else putStrLn ""

-- Incrementa el índice y continua el procesamiento
incrementarYContinuar :: IORef Int -> [(String, String)] -> IO ()
incrementarYContinuar nRef arrayParesEs = do
    modifyIORef nRef (+1)
    renglon nRef arrayParesEs

-- Función arbol que imprime algunos valores y luego ejecuta el bucle while
-- La función arbol ahora utilizará renglon correctamente y manejará los índices con IORef
-- Función principal para procesar la estructura del árbol
arbol :: [(String, String)] -> IO ()
arbol arrayParesEs = do
    putStr "S -> "
    putStrLn $ "      programa{RF"

    n <- newIORef 0
    let condition = do
            num <- readIORef n
            return (num < length arrayParesEs && primerValor num arrayParesEs /= "End")

    let action = do
            num <- readIORef n
            if primerValor num arrayParesEs /= "Comentario"
            then do
                putStrLn "            R -> TV=O RF |->"
                if primerValor num arrayParesEs == "D"
                then do
                    putStr $ "T -> " ++ segundoValor num arrayParesEs ++ " | "
                    modifyIORef n (+1)
                else putStrLn "T -> eps | "
                num' <- readIORef n
                putStr $ "V -> " ++ segundoValor num' arrayParesEs ++ " | = | "
                modifyIORef n (+2)
                num'' <- readIORef n
                putStr "O -> "
                renglon n arrayParesEs
                modifyIORef n (+1)
                putStr ""
            else do
                putStr $ "R -> " ++ segundoValor num arrayParesEs

    while condition action

    putStrLn "F -> }}"
    putStrLn "¡Proceso completado!"
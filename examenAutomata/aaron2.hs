import Data.IORef
import Control.Monad (when)
import System.IO
    ( hClose,
      hPutStr,
      hPutStrLn,
      withFile,
      IOMode(WriteMode, AppendMode) )

-- Declaración de un array
listaOut :: [(String, String)]
listaOut = 
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

arrayTipo :: Int -> String
arrayTipo n = fst (listaOut !! n)

arrayValor :: Int -> String
arrayValor n = snd (listaOut !! n)

escribirArchivo :: String -> IO ()
escribirArchivo linea = withFile "output.txt" AppendMode (\handle -> do
    hPutStrLn handle linea
    hClose handle
  )

pegarEnUltimaLinea :: FilePath -> String -> IO ()
pegarEnUltimaLinea archivo contenidoNuevo = do
    contenido <- readFile archivo
    let lineas = lines contenido
        nuevaUltimaLinea = if null lineas then contenidoNuevo else last lineas ++ contenidoNuevo
        nuevasLineas = init lineas ++ [nuevaUltimaLinea]
        nuevoContenido = unlines nuevasLineas
    putStrLn nuevoContenido
    writeFile archivo nuevoContenido

while :: IO Bool -> IO () -> IO ()
while cond accion = do
    c <- cond
    when c $ do
        accion
        while cond accion

operacion :: IORef Int -> IO ()
operacion nRef = do
    i <- readIORef nRef
    if i >= length listaOut
        then return ()
        else do
            if arrayTipo i == "Comentario"
                then do
                    let linea = arrayValor i ++ ", "
                    pegarEnUltimaLinea "output.txt" linea
                    putStrLn ""
                else do
                    when (arrayTipo i == "ParentesisAbre") $ do
                        let linea = arrayValor i ++ ", "
                        pegarEnUltimaLinea "output.txt" linea
                        let newQ = i + 1
                        writeIORef nRef newQ
                    i <- readIORef nRef
                    when (arrayTipo i == "Entero" || arrayTipo i == "Real" || arrayTipo i == "Variable") $ do
                        let linea = arrayValor i ++ ", "
                        pegarEnUltimaLinea "output.txt" linea
                        when (i + 1 < length listaOut && arrayTipo (i + 1) == "ParentesisCierra") $ do
                            let newQ = i + 1
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            let linea = arrayValor newQ ++ ", "
                            pegarEnUltimaLinea "output.txt" linea
                    i <- readIORef nRef
                    if i + 1 < length listaOut && arrayTipo (i+1) /= "Entero" && arrayTipo (i+1) /= "Real" && arrayTipo (i+1) /= "Variable" && arrayTipo (i+1) /= "Comentario" && arrayTipo (i+1) /= "ParentesisAbre" && arrayTipo (i+1) /= "ParentesisCierra" && arrayTipo (i+1) /= "Tipo" && arrayTipo (i+1) /= "Final"
                        then do
                            let newQ = i + 2
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            let linea = arrayValor (newQ-1) ++ ", "
                            pegarEnUltimaLinea "output.txt" linea
                            operacion nRef
                        else if i + 1 < length listaOut && arrayTipo(i+1) == "Comentario"
                            then do
                                let newQ = i + 1
                                writeIORef nRef newQ
                                let linea = arrayValor newQ ++ ", "
                                pegarEnUltimaLinea "output.txt" linea
                            else do
                                putStrLn ""
                                return ()

derivacionA :: IO ()
derivacionA = do
    escribirArchivo "S" 
    escribirArchivo "-------------------------------------------------" 
    escribirArchivo "IQF" 
    escribirArchivo "-------------------------------------------------" 
    escribirArchivo "Programa{" 
    escribirArchivo "   principal" 
    escribirArchivo "       {" 
    escribirArchivo "           Q" 
    escribirArchivo "       }" 
    escribirArchivo "}" 
    cond <- newIORef ""
    n <- newIORef 1
    let condition = do
            num <- readIORef n
            return (arrayTipo num /= "Final")
    let accion = do
            num <- readIORef n
            if arrayTipo num /= "Comentario"
                then do
                    escribirArchivo "           Q [Q1 = Q2] || "
                    if arrayTipo num == "Tipo" 
                        then do
                            let linea = "Q1 [A B] || A ["++ arrayValor num ++"] ||"
                            pegarEnUltimaLinea "output.txt" linea
                            writeIORef n (num + 1)
                        else pegarEnUltimaLinea "output.txt" "Q1 [B] || = || "
                    num <- readIORef n
                    let linea = "B [" ++ arrayValor num ++ "] || "
                    pegarEnUltimaLinea "output.txt" linea
                    writeIORef n (num + 2)
                    num <- readIORef n
                    pegarEnUltimaLinea "output.txt" "Q2 ["
                    operacion n
                    num <- readIORef n
                    writeIORef n (num + 1)
                    pegarEnUltimaLinea "output.txt" ";]"
                else do
                    let linea = "           Q [" ++ arrayValor num ++ "]"
                    escribirArchivo linea
    escribirArchivo "-------------------------------------------------" 
    escribirArchivo "Programa{" 
    escribirArchivo "   principal" 
    escribirArchivo "       {" 
    while condition accion
    escribirArchivo "       }" 
    escribirArchivo "}" 
limpiarArchivo :: FilePath -> IO ()
limpiarArchivo archivo = withFile archivo WriteMode (\handle -> hPutStr handle "")

main :: IO ()
main = do
    limpiarArchivo "output.txt"
    derivacionA
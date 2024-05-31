-- Aaron Hernandez Jimenez A01642529
-- Actividad - Examen analizador sintáctico
-- Fecha de entrega: 30/5/2024

import Control.Monad.RWS (MonadState (put)) -- Añadido import para manejar el estado del lexer
import Data.Char (isDigit, isLetter, isSpace, isUpper, toLower, toUpper) -- Añadido import para manejar caracteres
import Data.List (find, intercalate, isPrefixOf, isSuffixOf) -- Añadido import para manejar listas
import Distribution.Compat.CharParsing (tab) -- Añadido import para manejar tabulaciones
import Data.Tree
import Distribution.Simple.Build (build)

import Data.IORef
import Control.Monad (when)
import System.IO
    ( hClose,
      hPutStr,
      hPutStrLn,
      withFile,
      IOMode(WriteMode, AppendMode) )
import Data.Text.Array (new)



data Token -- Añadido token para manejar números enteros, reales, identificadores, comentarios, operadores y paréntesis
  = Entero String -- Añadido token para números enteros
  | Real String -- Añadido token para números reales
  | Asignacion -- Añadido token para el operador de asignación
  | Variable String -- Añadido token para identificadores
  | Tipo String -- Añadido token para el tipo de variable
  | Otro String -- Añadido token para otros tipos de variables
  | Comentario String -- Añadido token para comentarios
  | Multiplicacion -- Añadido token para el operador de multiplicación
  | Division -- Añadido token para el operador de división
  | Suma -- Añadido token para el operador de suma
  | Resta -- Añadido token para el operador de resta
  | Potencia -- Añadido token para el operador de potencia
  | ParentesAbierto -- Añadido token para el paréntesis izquierdo
  | ParentesCerrado -- Añadido token para el paréntesis derecho
  deriving (Show)

type LineNumber = Int -- numero de linea

type ValidationResult = Either String [Token] -- Ajustamos la función de validación para que devuelva Either String (para errores) o [Token] para una línea válida

-- Ajustamos la función de validación para que devuelva Either String (para errores) o [Token] para una línea válida

-- Añadido función para manejar el lexer
lexer :: String -> [Token] -- el lexer funciona para separar los tokens de la cadena de texto que se le pasa como parametro y regresa una lista de tokens
lexer [] = []
lexer ('/' : '/' : cs) = [Comentario ('/' : '/' : cs)] -- Maneja comentarios
lexer ('i' : 'n' : 't' : ' ' : cs) = Tipo "int" : lexer cs -- Añadido manejo del tipo int
lexer ('f' : 'l' : 'o' : 'a' : 't' : ' ' : cs) = Tipo "float" : lexer cs -- Añadido manejo del tipo float
lexer ('d' : 'o' : 'u' : 'b' : 'l' : 'e' : ' ' : cs) = Tipo "double" : lexer cs -- Añadido manejo del tipo double
lexer ('c' : 'h' : 'a' : 'r' : ' ' : cs) = Tipo "char" : lexer cs -- Añadido manejo del tipo char
lexer ('s' : 't' : 'r' : 'i' : 'n' : 'g' : ' ' : cs) = Tipo "string" : lexer cs -- Añadido manejo del tipo string
lexer ('b' : 'o' : 'o' : 'l' : ' ' : cs) = Tipo "bool" : lexer cs -- Añadido manejo del tipo bool
lexer ('v' : 'o' : 'i' : 'd' : ' ' : cs) = Tipo "void" : lexer cs -- Añadido manejo del tipo void
lexer ('c' : 'o' : 'n' : 's' : 't' : ' ' : cs) = Tipo "const" : lexer cs -- Añadido manejo del tipo const
lexer ('u' : 'n' : 's' : 'i' : 'g' : 'n' : 'e' : 'd' : ' ' : cs) = Tipo "unsigned" : lexer cs -- Añadido manejo del tipo unsigned
lexer ('l' : 'o' : 'n' : 'g' : ' ' : cs) = Tipo "long" : lexer cs -- Añadido manejo del tipo long
lexer ('s' : 'h' : 'o' : 'r' : 't' : ' ' : cs) = Tipo "short" : lexer cs -- Añadido manejo del tipo short
--entero, real, flotante, doble, caracter, cadena, booleano, vacio, constante, sin signo, largo, corto
lexer ('E' : 'n' : 't' : 'e' : 'r' : 'o' : cs) = Tipo "entero" : lexer cs -- Añadido manejo del tipo entero
lexer ('R' : 'e' : 'a' : 'l' : cs) = Tipo "real" : lexer cs -- Añadido manejo del tipo real
lexer ('F' : 'l' : 'o' : 't' : 'a' : 'n' : 't' : 'e' : cs) = Tipo "flotante" : lexer cs -- Añadido manejo del tipo flotante
lexer ('D' : 'o' : 'b' : 'l' : 'e' : cs) = Tipo "doble" : lexer cs -- Añadido manejo del tipo doble
lexer ('C' : 'a' : 'r' : 'a' : 'c' : 't' : 'e' : 'r' : cs) = Tipo "caracter" : lexer cs -- Añadido manejo del tipo caracter
lexer ('C' : 'a' : 'd' : 'e' : 'n' : 'a' : cs) = Tipo "cadena" : lexer cs -- Añadido manejo del tipo cadena



lexer (c : cs)
  | isDigit c || (c == '-' && not (null cs) && (isDigit (head cs) || head cs == '.')) = lexNumberOrReal (c : cs) -- Ajuste para números negativos
  | isLetter c = lexIdentifier (c : cs) -- Añadido manejo de identificadores
  | c == '=' = Asignacion : lexer cs -- Añadido manejo del operador de asignación
  | c == '+' = Suma : lexer cs -- Añadido manejo del operador de suma
  | c == '-' = Resta : lexer cs -- Añadido manejo del operador de resta
  | c == '/' = Division : lexer cs -- Añadido manejo del operador de división
  | c == '*' = Multiplicacion : lexer cs -- Añadido manejo del operador de multiplicación
  | c == '(' = ParentesAbierto : lexer cs -- Añadido manejo del paréntesis izquierdo
  | c == ')' = ParentesCerrado : lexer cs -- Añadido manejo del paréntesis derecho
  | c == '^' = Potencia : lexer cs -- Añadido manejo del operador de potencia
  | otherwise = lexer cs

-- Añadido función para manejar números
-- Función ajustada para manejar números, incluyendo negativos
-- funcion ajustada para manejar tambien los numeros reales
lexNumberOrReal :: String -> [Token]
lexNumberOrReal cs =
  let (num, rest) = span (\x -> isDigit x || x == '.' || x == 'E' || x == 'e' || x == '-' || (x == '-' && (not . null) cs && (isDigit (head cs) || head cs == '.'))) cs
   in case num of
        ('-' : '.' : _) -> Real num : lexer rest -- Maneja números reales negativos con punto decimal al inicio
        ('-' : _) ->
          if 'E' `elem` num || 'e' `elem` num || '.' `elem` num
            then Real num : lexer rest -- Números reales negativos con notación científica o punto decimal
            else Entero num : lexer rest -- Números enteros negativos
        _ ->
          if 'E' `elem` num || 'e' `elem` num || '.' `elem` num -- Maneja números reales y enteros
            then Real num : lexer rest -- Números reales
            else Entero num : lexer rest -- Números enteros

-- Añadido función para manejar variables
-- funcion mejorada para aceptar variables con numeros y guiones bajos
lexIdentifier :: String -> [Token]
lexIdentifier cs =
    let (ident, rest) = span (\x -> isLetter x || isDigit x || x == '_') cs
     in Variable ident : lexer rest

-- Funcion necesaria para convertir los tokens en string para la tabla.
-- esto es para que se pueda imprimir de manera mas facil
tokenToString :: Token -> String
tokenToString token = case token of
  Entero n -> "Entero\t\t\t" ++ n
  Real n -> "Real\t\t\t" ++ n
  Asignacion -> "Asignacion\t\t="
  Variable ident -> "Variable\t\t" ++ ident
  Tipo t -> "Tipo\t\t\t" ++ t
  Comentario c -> "Comentario\t\t" ++ c
  ParentesAbierto -> "ParentesAbre\t\t("
  ParentesCerrado -> "ParentesCierra\t\t)"
  Suma -> "Suma\t\t\t+"
  Resta -> "Resta\t\t\t-"
  Multiplicacion -> "Multiplicacion\t\t*"
  Division -> "Division\t\t/"
  Potencia -> "Potencia\t\t^"

-- Función para convertir la lista de tokens en una tabla
tokensToTable :: [Token] -> String
tokensToTable tokens =
  let headers = "\nTipo\t\t\tValor\n" ++ replicate 40 '-' ++ "\n" -- Añadido encabezado para la tabla
      rows = map tokenToString tokens -- Añadido conversión de tokens a strings
   in headers ++ intercalate "\n" rows -- Añadido concatenación de encabezado y filas de la tabla

-- funcion con automata determinista para aprobar el lexer

-- funcion para comprobar que sea correcto el uso de los inputs en input.txt

-- Función para validar el correcto uso de tokens en la lista de tokens
validateLineTokens :: [Token] -> ValidationResult -- Añadido tipo de retorno para la validación
validateLineTokens tokens
  | null tokens = Left "Linea vacia"
  | not $ validarParentesis tokens 0 = Left "Desequilibrio de parentesis"
  | not $ validarInicio tokens = Left "No inicia con una variable"
  | not $ validarOperadores tokens = Left "Operador sin operandos"
--  | not $ validarSiguiente tokens = Left "Token no valido despues de tipo-variable o variable-asignacion"
  | otherwise = Right tokens

-- Función para revisar que los paréntesis estén balanceados
processAndValidateLines :: [String] -> [(LineNumber, ValidationResult)]
processAndValidateLines lines = zipWith (\n line -> (n, validateLineTokens (lexer line))) [1 ..] lines

-- Función para reportar los resultados de la validación
reportValidationResults :: [(LineNumber, ValidationResult)] -> IO ()
reportValidationResults results = mapM_ reportResult results
  where
    reportResult (lineNum, Right _) = putStrLn $ "Linea " ++ show lineNum ++ ": Valida"
    reportResult (lineNum, Left errorMsg) = putStrLn $ "Linea " ++ show lineNum ++ " Error: " ++ errorMsg

-- Función para escribir las líneas válidas en output.txt y los errores en problemas.txt
writeValidAndInvalidLines :: [(LineNumber, ValidationResult)] -> IO ()
writeValidAndInvalidLines results = do
  let validLines = map (\(lineNum, Right tokens) -> (lineNum, tokens)) $ filter (\(_, result) -> case result of Right _ -> True; _ -> False) results
  let invalidLines = map (\(lineNum, Left errorMsg) -> (lineNum, errorMsg)) $ filter (\(_, result) -> case result of Left _ -> True; _ -> False) results
  writeFile "output.txt" $ intercalate "\n" $ map (tokensToTable . snd) validLines -- Escribir las líneas válidas en output.txt
  writeFile "problems.txt" $ intercalate "\n" $ map (\(lineNum, errorMsg) -> "Linea " ++ show lineNum ++ " Error: " ++ errorMsg) invalidLines

-- Función auxiliar para validar el correcto balance de paréntesis
validarParentesis :: [Token] -> Int -> Bool
validarParentesis [] 0 = True -- Caso base: no hay tokens y los paréntesis están balanceados
validarParentesis [] _ = False -- Caso base: no hay tokens pero los paréntesis no están balanceados
validarParentesis (t : ts) contador =
  case t of
    ParentesAbierto -> validarParentesis ts (contador + 1)
    ParentesCerrado -> if contador <= 0 then False else validarParentesis ts (contador - 1)
    _ -> validarParentesis ts contador


-- Función para validar el inicio correcto de una línea de código
validarInicio :: [Token] -> Bool
validarInicio [] = False
validarInicio (t:ts) = case t of
  Tipo _ -> case ts of  -- Asume que después de un tipo debe seguir una variable
    (Variable _ : _) -> True
    _ -> False
  Variable _ -> True  -- Acepta una línea que comienza directamente con una variable
  Comentario _ -> True  -- Acepta comentarios al inicio de la línea
  _ -> False


-- Función auxiliar para validar lo que sigue después de tipo y variable o variable y asignación
validarSiguiente :: [Token] -> Bool
validarSiguiente [] = True -- No hay más tokens, es válido
validarSiguiente (x:xs) = case x of
  Asignacion -> True -- Aceptar si sigue una asignación
  _ -> False -- Cualquier otra cosa no es válida después de tipo-variable o variable-asignación



-- Función para revisar que todos los operadores tengan como mínimo un operando a la izquierda y a la derecha
validarOperadores :: [Token] -> Bool
validarOperadores [] = True
validarOperadores [t] = case t of -- Caso base: solo hay un token
  Suma -> False
  Resta -> False
  Multiplicacion -> False
  Division -> False
  Potencia -> False
  _ -> True
validarOperadores (t : ts) = case t of -- Caso recursivo: hay más de un token y se revisa el primer token
-- se revisa la suma y la resta para ver si hay un operando a la izquierda y a la derecha
  Suma -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesAbierto -> validarOperadores ts
    _ -> False
  Resta -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesAbierto -> validarOperadores ts
    _ -> False
  -- se revisa la multiplicacion y la division para ver si hay un operando a la izquierda y a la derecha
  Multiplicacion -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesAbierto -> validarOperadores ts
    _ -> False
  Division -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesAbierto -> validarOperadores ts
    _ -> False
  -- se revisa la potencia para ver si hay un operando a la izquierda y a la derecha
  Potencia -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesAbierto -> validarOperadores ts
    _ -> False
  _ -> validarOperadores ts

 -- Función para validar la estructura global del programa
validarEstructuraGlobal :: [String] -> Maybe String
validarEstructuraGlobal lines = 
  let allContent = concatMap (filter (not . isSpace)) lines  -- Concatena todo removiendo espacios
  in if "Programa{principal{" `isPrefixOf` allContent && "}}" `isSuffixOf` allContent
     then Nothing
     else Just "Error: El programa debe empezar con 'Programa { principal {' y terminar con '} }'."

-- Añadir función trim para eliminar espacios en blanco
-- Añadir función trim para eliminar espacios en blanco (opcional ya que usamos filter para limpiar espacios)
trim :: String -> String
trim = f . f
   where f = reverse . dropWhile isSpace

-- Añadir función treeFromTokens para generar un árbol de tokens
-- Generar un árbol de derivación simple basado en los tokens
treeFromTokens :: [Token] -> Tree String
treeFromTokens tokens = Node "Program" (map tokenToNode tokens)

-- Convertir un token a un nodo del árbol
tokenToNode :: Token -> Tree String
tokenToNode token = Node (tokenToString token) []


-- Función para escribir el árbol en un archivo
writeTreeToFile :: Tree String -> IO ()
writeTreeToFile tree = do
  let treeString = drawTree tree
  writeFile "arbol.txt" treeString
  putStrLn "Árbol de derivación guardado en arbol.txt"

--FINAL DE FUNCIONES DE LEXER

--INICIO DE FUNCIONES DE ARBOL DE DERIVACION


-- Declaración de un array

type ParsedList = [(String, String)]





arrayTipo :: Int -> [(String, String)] -> String
arrayTipo n updatedList = fst (updatedList !! n)

arrayValor :: Int -> [(String, String)] -> String
arrayValor n updatedList = snd (updatedList !! n)


escribirArchivo :: String -> IO ()
escribirArchivo linea = withFile "arbol.txt" AppendMode (\handle -> do
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

operacion :: [(String, String)] -> IORef Int -> IO ()
operacion updatedList nRef = do
    i <- readIORef nRef
    if i >= length updatedList
        then return ()
        else do
            if arrayTipo i updatedList == "Comentario"
                then do
                    let linea = arrayValor i updatedList ++ ", "
                    pegarEnUltimaLinea "arbol.txt" linea
                    putStrLn ""
                else do
                    when (arrayTipo i updatedList == "ParentesisAbre") $ do
                        let linea = arrayValor i updatedList ++ ", "
                        pegarEnUltimaLinea "arbol.txt" linea
                        let newQ = i + 1
                        writeIORef nRef newQ
                    i <- readIORef nRef
                    when (arrayTipo i updatedList == "Entero" || arrayTipo i updatedList == "Real" || arrayTipo i updatedList == "Variable") $ do
                        let linea = arrayValor i updatedList ++ ", "
                        pegarEnUltimaLinea "arbol.txt" linea
                        when (i + 1 < length updatedList && arrayTipo (i + 1) updatedList == "ParentesisCierra") $ do
                            let newQ = i + 1
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            let linea = arrayValor newQ updatedList ++ ", "
                            pegarEnUltimaLinea "arbol.txt" linea
                    i <- readIORef nRef
                    if i + 1 < length updatedList && arrayTipo (i+1) updatedList /= "Entero" && arrayTipo (i+1) updatedList /= "Real" && arrayTipo (i+1) updatedList /= "Variable" && arrayTipo (i+1) updatedList /= "Comentario" && arrayTipo (i+1) updatedList /= "ParentesisAbre" && arrayTipo (i+1) updatedList /= "ParentesisCierra" && arrayTipo (i+1) updatedList /= "Tipo" && arrayTipo (i+1) updatedList /= "Final"
                        then do
                            let newQ = i + 2
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            let linea = arrayValor (newQ-1) updatedList ++ ", "
                            pegarEnUltimaLinea "arbol.txt" linea
                            operacion updatedList nRef
                        else if i + 1 < length updatedList && arrayTipo(i+1) updatedList == "Comentario"
                            then do
                                let newQ = i + 1
                                writeIORef nRef newQ
                                let linea = arrayValor newQ updatedList ++ ", "
                                pegarEnUltimaLinea "arbol.txt" linea
                            else do
                                putStrLn ""
                                return ()



derivacionA :: [(String, String)] -> IO ()
derivacionA updatedList = do
    -- Escribe solo una vez el encabezado y el comienzo del programa.
    escribirArchivo "S" 
    escribirArchivo "-------------------------------------------------" 
    escribirArchivo "IQF" 
    escribirArchivo "-------------------------------------------------" 
    escribirArchivo "Programa{" 
    escribirArchivo "   principal" 
    escribirArchivo "       {" 
    n <- newIORef 1
    let condition = do
            num <- readIORef n
            return (arrayTipo num updatedList /= "Final")
    let accion = do
            num <- readIORef n
            if arrayTipo num updatedList /= "Comentario"
                then do
                    escribirArchivo "           Q [Q1 = Q2] || "
                    if arrayTipo num updatedList == "Tipo" 
                        then do
                            let linea = "Q1 [A B] || A ["++ arrayValor num updatedList ++"] ||"
                            pegarEnUltimaLinea "arbol.txt" linea
                            writeIORef n (num + 1)
                        else pegarEnUltimaLinea "arbol.txt" "Q1 [B] || = || "
                    num <- readIORef n
                    let linea = "B [" ++ arrayValor num updatedList ++ "] || "
                    pegarEnUltimaLinea "arbol.txt" linea
                    writeIORef n (num + 2)
                    num <- readIORef n
                    pegarEnUltimaLinea "arbol.txt" "Q2 ["
                    operacion updatedList n
                    num <- readIORef n
                    writeIORef n (num + 1)
                    pegarEnUltimaLinea "arbol.txt" ";]"
                else do
                    let linea = "           Q [" ++ arrayValor num updatedList ++ "]"
                    escribirArchivo linea
    -- Comienza a ejecutar las acciones solo después de configurar todo.
    while condition accion
    escribirArchivo "       }" 
    escribirArchivo "}" 
    escribirArchivo "-------------------------------------------------" 



-- Función para limpiar un archivo    
limpiarArchivo :: FilePath -> IO ()
limpiarArchivo archivo = withFile archivo WriteMode (\handle -> hPutStr handle "")



-- Función principal del programa
--FIN DEL ARBOL DE DERIVACION

-- Función para actualizar la lista basada en el contenido del archivo
updateListaOut :: String -> ParsedList
updateListaOut content = [("Inicio", "Programa{principal{")] ++ parseOutput (lines content) ++ [("Final", "}}")]



-- Supongamos que esta es una función que podría procesar la lista y hacer algo útil
processList :: ParsedList -> Int
processList list = length list  -- Ejemplo: devuelve la cantidad de elementos

-- Function to parse the file lines into [(String, String)]
-- Function to parse the file lines into [(String, String)]
parseOutput :: [String] -> [(String, String)]
parseOutput [] = []
parseOutput (x:xs)
    | x == "Tipo\t\t\tValor" || x == "----------------------------------------" = parseOutput xs
    | otherwise = 
        let (block, rest) = span (/= "----------------------------------------") xs
        in parseBlock block ++ parseOutput (dropWhile (== "----------------------------------------") rest)

-- Helper function to parse each block of lines
parseBlock :: [String] -> [(String, String)]
parseBlock [] = []
parseBlock (line:xs)
    | null line = parseBlock xs  -- Ignore empty lines
    | otherwise =
        let (tipo, valor) = parseLine line
            tipoMapped = mapType tipo
        in if tipoMapped == "Unknown" then parseBlock xs  -- Ignore unknown types
           else (tipoMapped, valor) : parseBlock xs

-- Function to parse a single line into (Tipo, Valor)
parseLine :: String -> (String, String)
parseLine line =
    let (tipo, valor) = break (== '\t') line
    in (tipo, dropWhile (== '\t') (drop 1 valor))

-- Function to map the type strings to desired output
mapType :: String -> String
mapType "Variable" = "Variable"
mapType "Asignacion" = "Igual"
mapType "Entero" = "Entero"
mapType "Real" = "Real"
mapType "Suma" = "Suma"
mapType "Resta" = "Resta"
mapType "Division" = "Division"
mapType "Potencia" = "Potencia"
mapType "Multiplicacion" = "Multi"
mapType "ParentesAbre" = "ParentesisAbre"
mapType "ParentesCierra" = "ParentesisCierra"
mapType "Comentario" = "Comentario"
mapType _ = "Unknown"

-- Function to decide if a block should be ignored
shouldIgnoreBlock :: [String] -> Bool
shouldIgnoreBlock block =
    let lines = filter (not . null) block
        values = map (snd . parseLine) lines
    in "Programa" `elem` values || "principal" `elem` values

finalListaOut :: IO [(String, String)]
finalListaOut = do
    content <- readFile "output.txt"
    let linesOfFile = lines content
    let parsedList = parseOutput linesOfFile
    -- Add the initial and final elements to the parsed list
    return ([("Inicio", "Programa{principal{")] ++ parsedList ++ [("Final", "}}")])

    



-- FUNCION PRINCIPAL MAIN PARA EJECUTAR EL PROGRAMA
main :: IO ()
main = do
  putStrLn "Analizando el archivo input.txt..."
  contents <- readFile "input.txt"
  let linesOfContents = lines contents
  let estructuraValida = validarEstructuraGlobal linesOfContents
  case estructuraValida of
    Just errorMsg -> putStrLn errorMsg
    Nothing -> do
      putStrLn "Estructura del programa{principal {}} válida."
      let validationResults = processAndValidateLines linesOfContents
      reportValidationResults validationResults
      let tokens = concatMap lexer linesOfContents
      let table = tokensToTable tokens
      let tree = treeFromTokens tokens
      writeValidAndInvalidLines validationResults
      --Añadido para escribir el árbol en un archivo arbol.txt y limpiarlo antes de escribir

      --result <- finalListaOut
      --print result
      --content <- readFile "output.txt"
      --let updatedList = updateListaOut content listaOut
      --print updatedList
      --hacemos que listaOut sea igual a parsedOutput

      content <- readFile "output.txt"
      let updatedList = updateListaOut content  -- Crea la lista actualizada
      -- Llamada a otra función que necesita usar updatedList
      print updatedList

      limpiarArchivo "arbol.txt"
      derivacionA updatedList
      putStrLn "Tabla generada en output.txt"
      putStrLn "Guardando los problemas en problemas.txt"
      putStrLn "Guardando el árbol de derivación en arbol.txt"
  putStrLn "Análisis completado."
  
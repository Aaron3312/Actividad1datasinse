

import Data.Tree
import Data.List 
import System.IO
import Data.Text.Array 
import Distribution.Simple.Build (build)

import Data.Char 

import Data.IORef
import Control.Monad (when)
import Control.Monad.RWS (MonadState (put)) 



data Token 
  = Entero String 
  | Real String 
  | Asignacion 
  | Variable String 
  | Tipo String 
  | Otro String 
  | Comentario String 
  | Multiplicacion 
  | Division
  | Suma 
  | Resta 
  | Potencia 
  | ParentesAbierto 
  | ParentesCerrado 
  deriving (Show)

type LineNumber = Int 

type ValidationResult = Either String [Token] 

lexer :: String -> [Token] 
lexer [] = []
lexer ('/' : '/' : cs) = [Comentario ('/' : '/' : cs)]
lexer ('i' : 'n' : 't' : ' ' : cs) = Tipo "int" : lexer cs 
lexer ('f' : 'l' : 'o' : 'a' : 't' : ' ' : cs) = Tipo "float" : lexer cs 
lexer ('d' : 'o' : 'u' : 'b' : 'l' : 'e' : ' ' : cs) = Tipo "double" : lexer cs 
lexer ('c' : 'h' : 'a' : 'r' : ' ' : cs) = Tipo "char" : lexer cs 
lexer ('s' : 't' : 'r' : 'i' : 'n' : 'g' : ' ' : cs) = Tipo "string" : lexer cs 
lexer ('b' : 'o' : 'o' : 'l' : ' ' : cs) = Tipo "bool" : lexer cs 
lexer ('v' : 'o' : 'i' : 'd' : ' ' : cs) = Tipo "void" : lexer cs 
lexer ('c' : 'o' : 'n' : 's' : 't' : ' ' : cs) = Tipo "const" : lexer cs 
lexer ('u' : 'n' : 's' : 'i' : 'g' : 'n' : 'e' : 'd' : ' ' : cs) = Tipo "unsigned" : lexer cs 
lexer ('l' : 'o' : 'n' : 'g' : ' ' : cs) = Tipo "long" : lexer cs 
lexer ('s' : 'h' : 'o' : 'r' : 't' : ' ' : cs) = Tipo "short" : lexer cs 
lexer ('E' : 'n' : 't' : 'e' : 'r' : 'o' : cs) = Tipo "entero" : lexer cs 
lexer ('R' : 'e' : 'a' : 'l' : cs) = Tipo "real" : lexer cs 
lexer ('F' : 'l' : 'o' : 't' : 'a' : 'n' : 't' : 'e' : cs) = Tipo "flotante" : lexer cs 
lexer ('D' : 'o' : 'b' : 'l' : 'e' : cs) = Tipo "doble" : lexer cs 
lexer ('C' : 'a' : 'r' : 'a' : 'c' : 't' : 'e' : 'r' : cs) = Tipo "caracter" : lexer cs 
lexer ('C' : 'a' : 'd' : 'e' : 'n' : 'a' : cs) = Tipo "cadena" : lexer cs 



lexer (c : cs)
  | isDigit c || (c == '-' && not (null cs) && (isDigit (head cs) || head cs == '.')) = lexNumberOrReal (c : cs) 
  | isLetter c = lexIdentifier (c : cs) 
  | c == '=' = Asignacion : lexer cs 
  | c == '+' = Suma : lexer cs 
  | c == '-' = Resta : lexer cs 
  | c == '/' = Division : lexer cs 
  | c == '*' = Multiplicacion : lexer cs 
  | c == '(' = ParentesAbierto : lexer cs 
  | c == ')' = ParentesCerrado : lexer cs 
  | c == '^' = Potencia : lexer cs 
  | otherwise = lexer cs


lexNumberOrReal :: String -> [Token]
lexNumberOrReal cs =
  let (num, rest) = span (\x -> isDigit x || x == '.' || x == 'E' || x == 'e' || x == '-' || (x == '-' && (not . null) cs && (isDigit (head cs) || head cs == '.'))) cs
   in case num of
        ('-' : '.' : _) -> Real num : lexer rest 
        ('-' : _) ->
          if 'E' `elem` num || 'e' `elem` num || '.' `elem` num
            then Real num : lexer rest 
            else Entero num : lexer rest 
        _ ->
          if 'E' `elem` num || 'e' `elem` num || '.' `elem` num 
            then Real num : lexer rest 
            else Entero num : lexer rest 


lexIdentifier :: String -> [Token]
lexIdentifier cs =
    let (ident, rest) = span (\x -> isLetter x || isDigit x || x == '_') cs
     in Variable ident : lexer rest


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

tokensToTable :: [Token] -> String
tokensToTable tokens =
  let headers = "\nTipo\t\t\tValor\n" ++ replicate 40 '-' ++ "\n" 
      rows = map tokenToString tokens 
   in headers ++ intercalate "\n" rows 



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




type ParsedList = [(String, String)] --esto es mio


--banfunction
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
renglon :: IORef Int -> [(String, String)] -> IO ()
renglon nRef arrayParesEs = do
    i <- readIORef nRef
    if i >= length arrayParesEs
        then return ()
        else do
            if primerValor i arrayParesEs== "C"
                then do
                    putStr (segundoValor i arrayParesEs)
                    putStrLn ""
                else do
                    when (primerValor i arrayParesEs== "PA") $ do
                        putStr (segundoValor i arrayParesEs ++ " | ")
                        let newQ = i + 1
                        writeIORef nRef newQ
                    i <- readIORef nRef
                    when (primerValor i arrayParesEs== "E" || primerValor i arrayParesEs == "Rl" || primerValor i arrayParesEs== "V") $ do
                        putStr (segundoValor i arrayParesEs)
                        when (i + 1 < length arrayParesEs && primerValor (i + 1) arrayParesEs == "PC") $ do
                            let newQ = i + 1
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            putStr (" | " ++ segundoValor newQ arrayParesEs)
                    i <- readIORef nRef
                    if i + 1 < length arrayParesEs && primerValor (i+1) arrayParesEs /= "E" && primerValor (i+1) arrayParesEs/= "Rl" && primerValor (i+1) arrayParesEs /= "V" && primerValor (i+1) arrayParesEs /= "Comentario" && primerValor (i+1) arrayParesEs /= "PA" && primerValor (i+1) arrayParesEs /= "PC" && primerValor (i+1)  arrayParesEs/= "D" && primerValor (i+1) arrayParesEs /= "End"
                        then do
                            let newQ = i + 2
                            writeIORef nRef newQ
                            i <- readIORef nRef
                            putStr (" | " ++ segundoValor (newQ-1) arrayParesEs ++ " | ")
                            renglon nRef arrayParesEs
                        else if i + 1 < length arrayParesEs && primerValor(i+1) arrayParesEs == "Comentario"
                            then do
                                let newQ = i + 1
                                writeIORef nRef newQ
                                putStrLn (" | " ++ segundoValor newQ arrayParesEs)
                            else do
                                putStrLn ""
                                return ()

-- Función arbol que imprime algunos valores y luego ejecuta el bucle while
arbol :: [(String, String)] -> IO ()
arbol arrayParesEs = do
    putStr "S -> "
    putStrLn (segundoValor 0 arrayParesEs)
    putStr "      programa{"
    putStrLn " RF"
    putStrLn ""
    
    ref <- newIORef ""
    n <- newIORef 1
    let condition = do
            num <- readIORef n
            return (primerValor num arrayParesEs /= "End")
    let action = do
            num <- readIORef n
            if primerValor num arrayParesEs /= "Comentario"
                then do
                    putStr "            R -> TV=O RF |->"
                    if primerValor num arrayParesEs == "D"
                        then do
                            putStr ("T -> " ++ segundoValor num arrayParesEs ++ " | " )
                            writeIORef n (num + 1)
                        else putStr "T -> eps | "
                    num <- readIORef n
                    putStr ("V -> " ++ segundoValor num arrayParesEs ++ " | = | ")
                    writeIORef n (num + 2)
                    num <- readIORef n
                    putStr "O -> "
                    renglon n arrayParesEs
                    num <- readIORef n
                    writeIORef n (num + 1)
                    putStr ""
                else putStrLn ("R -> "++ segundoValor num arrayParesEs)
    while condition action
    putStrLn ""
    putStrLn "F -> }}"
    putStrLn "¡Proceso completado!"

--mi funcion

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



-- Función para limpiar un archivo    
limpiarArchivo :: FilePath -> IO ()
limpiarArchivo archivo = withFile archivo WriteMode (\handle -> hPutStr handle "")





--FIN DEL ARBOL DE DERIVACION

-- Función para actualizar la lista basada en el contenido del archivo
updateListaOut :: String -> ParsedList
updateListaOut content = [("S", "Programa{")] ++ parseOutput (lines content) ++ [("End", "}}")]



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

mapType :: String -> String
mapType "Variable" = "V"
mapType "Asignacion" = "Igual"
mapType "Entero" = "E"
mapType "Real" = "Rl"
mapType "Suma" = "+"
mapType "Multiplicacion" = "Multi"
mapType "Resta" = "Resta"
mapType "Division" = "Division"
mapType "Potencia" = "Exp"
mapType "ParentesAbre" = "PA"
mapType "ParentesCierra" = "PC"
mapType "Comentario" = "Comentario"
mapType _ = "Unknown"

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
    return ([("S", "Programa{")] ++ parsedList ++ [("End", "}}")])

-- ###############FINAL DE FUNCIONES DE ARBOL DE DERIVACION####################
    



-- FUNCION PRINCIPAL MAIN
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
      arbol updatedList 



      putStrLn "Listo."
  putStrLn "Análisis completado."
  
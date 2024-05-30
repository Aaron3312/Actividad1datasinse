-- Aaron Hernandez Jimenez A01642529
-- Actividad 2.3 - Examen de Haskell
-- Fecha de entrega: 20/3/2024

import Control.Monad.RWS (MonadState (put))
import Data.Char (isDigit, isLetter, isSpace, isUpper, toLower, toUpper)
import Data.List (find, intercalate, isPrefixOf, isSuffixOf)
import Distribution.Compat.CharParsing (tab)



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

-- Función para probar el lexer con un archivo
main :: IO ()
main = do
  putStrLn "Analizando el archivo input.txt..."
  contents <- readFile "input.txt"
  let linesOfContents = lines contents
  let estructuraValida = validarEstructuraGlobal linesOfContents
  case estructuraValida of
    Just errorMsg -> putStrLn errorMsg
    Nothing -> do
      putStrLn "Estructura del programa válida."
      let validationResults = processAndValidateLines linesOfContents
      reportValidationResults validationResults
      let tokens = concatMap lexer linesOfContents
      let table = tokensToTable tokens
      writeValidAndInvalidLines validationResults
      putStrLn "Tabla generada en output.txt"
      putStrLn "Guardando los problemas en problemas.txt"
  putStrLn "Análisis completado."
  
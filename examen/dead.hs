import Data.Char (isDigit, isLetter)
import Data.List (intercalate, find)
import Distribution.Compat.CharParsing (tab)
import Control.Monad.RWS (MonadState(put))

data Token -- Añadido token para manejar números enteros, reales, identificadores, comentarios, operadores y paréntesis
  = Entero String -- Añadido token para números enteros
  | Real String -- Añadido token para números reales
  | Asignacion -- Añadido token para el operador de asignación
  | Variable String -- Añadido token para identificadores
  | Comentario String -- Añadido token para comentarios
  | Operador String -- Añadido token para operadores
  | Multiplicacion -- Añadido token para el operador de multiplicación
  | Division -- Añadido token para el operador de división
  | Suma -- Añadido token para el operador de suma
  | Resta -- Añadido token para el operador de resta
  | Potencia -- Añadido token para el operador de potencia
  | ParentesisOpen -- Añadido token para el paréntesis izquierdo
  | ParentesisCierre -- Añadido token para el paréntesis derecho
  deriving (Show)

type LineNumber = Int -- numero de linea
type ValidationResult = Either String [Token] -- Ajustamos la función de validación para que devuelva Either String (para errores) o [Token] para una línea válida

-- Ajustamos la función de validación para que devuelva Either String (para errores) o [Token] para una línea válida


-- Añadido función para manejar el lexer
lexer :: String -> [Token]
lexer [] = []
lexer ('/' : '/' : cs) = [Comentario ('/' : '/' : cs)] -- Maneja comentarios
lexer (c : cs)
  | isDigit c || (c == '-' && not (null cs) && (isDigit (head cs) || head cs == '.')) = lexNumberOrReal (c : cs) -- Ajuste para números negativos
  | isLetter c = lexIdentifier (c : cs) -- Añadido manejo de identificadores
  | c == '=' = Asignacion : lexer cs -- Añadido manejo del operador de asignación
  | c == '+' = Suma : lexer cs -- Añadido manejo del operador de suma
  | c == '-' = Resta : lexer cs -- Añadido manejo del operador de resta
  | c == '/' = Division : lexer cs -- Añadido manejo del operador de división
  | c == '*' = Multiplicacion : lexer cs -- Añadido manejo del operador de multiplicación
  | c == '(' = ParentesisOpen : lexer cs -- Añadido manejo del paréntesis izquierdo
  | c == ')' = ParentesisCierre : lexer cs -- Añadido manejo del paréntesis derecho
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
          if 'E' `elem` num || 'e' `elem` num || '.' `elem` num
            then Real num : lexer rest
            else Entero num : lexer rest


-- Añadido función para manejar variables
-- funcion mejorada para aceptar variables con numeros y guiones bajos
lexIdentifier :: String -> [Token]
lexIdentifier cs =
  let (ident, rest) = span (\x -> isDigit x || isLetter x || x == '_') cs
   in Variable ident : lexer rest

--Funcion necesaria para convertir los tokens en string para la tabla.
tokenToString :: Token -> String
tokenToString token = case token of
  Entero n -> "Entero\t\t\t" ++ n
  Real n -> "Real\t\t\t" ++ n
  Asignacion -> "Asignacion\t\t="
  Variable ident -> "Variable\t\t" ++ ident
  Comentario c -> "Comentario\t\t" ++ c
  Operador op -> "Operador\t\t" ++ op
  ParentesisOpen -> "ParentesAbre\t\t("
  ParentesisCierre -> "ParentesCierra\t\t)"
  Suma -> "Suma\t\t\t+"
  Resta -> "Resta\t\t\t-"
  Multiplicacion -> "Multiplicacion\t\t*"
  Division -> "Division\t\t/"
  Potencia -> "Potencia\t\t^"

-- Función para convertir la lista de tokens en una tabla
tokensToTable :: [Token] -> String
tokensToTable tokens =
  let headers = "\nTipo\t\t\tValor\n" ++ replicate 40 '-' ++ "\n"
      rows = map tokenToString tokens
   in headers ++ intercalate "\n" rows

--funcion con automata determinista para aprobar el lexer 

--funcion para comprobar que sea correcto el uso de los inputs en input.txt


-- Función para validar el correcto uso de tokens en la lista de tokens
validateLineTokens :: [Token] -> ValidationResult
validateLineTokens tokens
  | null tokens = Left "Linea vacia"
  | not $ validarParentesis tokens 0 = Left "Desequilibrio de parentesis"
  | not $ validarInicio tokens = Left "No inicia con una variable"
  | not $ validarOperadores tokens = Left "Operador sin operandos"
  | otherwise = Right tokens



processAndValidateLines :: [String] -> [(LineNumber, ValidationResult)]
processAndValidateLines lines = zipWith (\n line -> (n, validateLineTokens (lexer line))) [1..] lines

reportValidationResults :: [(LineNumber, ValidationResult)] -> IO ()
reportValidationResults results = mapM_ reportResult results
  where
    reportResult (lineNum, Right _) = putStrLn $ "Linea " ++ show lineNum ++ ": Valida"
    reportResult (lineNum, Left errorMsg) = putStrLn $ "Linea " ++ show lineNum ++ " Error: " ++ errorMsg


writeValidAndInvalidLines :: [(LineNumber, ValidationResult)] -> IO ()
writeValidAndInvalidLines results = do
  let validLines = map (\(lineNum, Right tokens) -> (lineNum, tokens)) $ filter (\(_, result) -> case result of { Right _ -> True; _ -> False }) results
  let invalidLines = map (\(lineNum, Left errorMsg) -> (lineNum, errorMsg)) $ filter (\(_, result) -> case result of { Left _ -> True; _ -> False }) results
  writeFile "output.txt" $ intercalate "\n" $ map (tokensToTable . snd) validLines -- Escribir las líneas válidas en output.txt
  writeFile "problemas.txt" $ intercalate "\n" $ map (\(lineNum, errorMsg) -> "Linea " ++ show lineNum ++ " Error: " ++ errorMsg) invalidLines


-- Función auxiliar para validar el correcto balance de paréntesis
validarParentesis :: [Token] -> Int -> Bool
validarParentesis [] 0 = True -- Caso base: no hay tokens y los paréntesis están balanceados
validarParentesis [] _ = False -- Caso base: no hay tokens pero los paréntesis no están balanceados
validarParentesis (t:ts) contador =
    case t of
        ParentesisOpen ->  validarParentesis ts (contador + 1)
        ParentesisCierre -> if contador <= 0 then False else validarParentesis ts (contador - 1)
        _ -> validarParentesis ts contador

-- funcion auxiliar para validar el correcto uso de que al inicio siempre exista una variable o un comentario, al igual que unicamente debe de haber la variable seguida de una asignacion
validarInicio :: [Token] -> Bool
validarInicio [] = False
validarInicio [t] = case t of
  Variable _ -> True
  Comentario _ -> True
  _ -> False
validarInicio (t:ts) = case t of
  Variable _ -> case head ts of
    Asignacion -> True
    _ -> False
  Comentario _ -> True
  _ -> False
  
  

-- Función para revisar que todos los operadores tengan como mínimo un operando a la izquierda y a la derecha
validarOperadores :: [Token] -> Bool
validarOperadores [] = True
validarOperadores [t] = case t of
  Suma -> False
  Resta -> False
  Multiplicacion -> False
  Division -> False
  Potencia -> False
  _ -> True
validarOperadores (t:ts) = case t of
  Suma -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesisOpen -> validarOperadores ts
    _ -> False
  Resta -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesisOpen -> validarOperadores ts
    _ -> False
  Multiplicacion -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesisOpen -> validarOperadores ts
    _ -> False
  Division -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesisOpen -> validarOperadores ts
    _ -> False
  Potencia -> case head ts of
    Variable _ -> validarOperadores ts
    Entero _ -> validarOperadores ts
    Real _ -> validarOperadores ts
    ParentesisOpen -> validarOperadores ts
    _ -> False
  _ -> validarOperadores ts


-- Función para probar el lexer con un archivo
main :: IO ()
main = do
  putStrLn "Analizando el archivo input.txt..."
  contents <- readFile "input.txt"
  let linesOfContents = lines contents
  let validationResults = processAndValidateLines linesOfContents
  reportValidationResults validationResults
  putStrLn "Análisis completado."
  let tokens = concatMap lexer (lines contents)
  let table = tokensToTable tokens
  writeValidAndInvalidLines validationResults
  putStrLn "Tabla generada en output.txt"
  putStrLn "guardando los problemas en problemas.txt"

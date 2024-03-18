import Data.Char (isDigit, isLetter)
import Data.List (intercalate)
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

-- Añadido función para manejar identificadores
lexIdentifier :: String -> [Token]
lexIdentifier cs =
  let (ident, rest) = span (\x -> isDigit x || isLetter x || x == '_') cs
   in Variable ident : lexer rest

-- Definir la función que convierte un token en una representación de string para la fila de una tabla
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
  let headers = "Tipo\t\t\tValor\n" ++ replicate 40 '-' ++ "\n"
      rows = map tokenToString tokens
   in headers ++ intercalate "\n" rows

--funcion con automata determinista para aprobar el lexer 

--funcion que lea cuantas veces se repite un salto de linea en el txt
saltoDeLinea :: String -> Int
saltoDeLinea [] = 1
saltoDeLinea (x:xs) = if x == '\n' then 1 + saltoDeLinea xs else saltoDeLinea xs

--funcion que con los saltos de linea cuenta cuantos hay con algo escrito
saltoDeLineaConTexto :: String -> Int
saltoDeLineaConTexto [] = 0
saltoDeLineaConTexto (x:xs) = if x == '\n' then if (length xs) > 0 then if (head xs) /= '\n' then 1 + saltoDeLineaConTexto xs else saltoDeLineaConTexto xs else 0 else saltoDeLineaConTexto xs

--funcion para comprobar que sea correcto el uso de los tokens


-- Función para probar el lexer con un archivo
main :: IO ()
main = do
  putStrLn "Lexer"
  contents <- readFile "input.txt"
  let salto = saltoDeLinea contents
  let saltoConTexto = saltoDeLineaConTexto contents 
  let tokens = concatMap lexer (lines contents)
  let table = tokensToTable tokens
  print tokens
  putStrLn $ "Cantidad de saltos de linea: " ++ show salto
  putStrLn $ "Cantidad de saltos de linea con texto: " ++ show saltoConTexto
  putStrLn table
  writeFile "output.txt" table
  if correcto tokens then putStrLn "Correcto" else putStrLn "Incorrecto"
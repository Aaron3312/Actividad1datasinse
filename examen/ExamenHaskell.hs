type Token = (String, String) -- (Valor del Token, Tipo de Token)
type Estado = String
type Entrada = String

-- Función que inicia el análisis léxico
analizar :: String -> [Token]
analizar entrada = analizarDesdeEstado "inicio" entrada

-- Función que analiza la entrada desde un estado dado
analizarDesdeEstado :: Estado -> Entrada -> [Token]
analizarDesdeEstado _ [] = [] -- Caso base, cuando no hay más entrada
analizarDesdeEstado estado (c:cs) =
    let (nuevoEstado, token) = transicion estado c
    in case token of
        Just t  -> t : analizarDesdeEstado nuevoEstado cs -- Token reconocido
        Nothing -> analizarDesdeEstado nuevoEstado cs -- No hay token reconocido aún

-- Función de transición del AFD
transicion :: Estado -> Char -> (Estado, Maybe Token)
transicion estado char =
    -- Aquí iría la lógica de transición basada en el estado y el char
    -- Deberías retornar el nuevo estado y, opcionalmente, un token reconocido

numDia d m a =
    (d + floor(fromIntegral(13*(m'+1))/5) + a' + floor(fromIntegral a'/4) + floor(fromIntegral j/4) - 2*j) `mod` 7
  where
    (m', a') = if m < 3 then (m + 12, a - 1) else (m, a)
    j = floor(fromIntegral a' / 100)

diaSemana a m d = do
    let resultado =  (numDia d m a)
    if resultado == 0
        then putStrLn "Naciste un Viernes."
    else if resultado == 1
        then putStrLn "Naciste un Sabado."
    else if resultado == 2
        then putStrLn "Naciste un Domingo."
    else if resultado == 3
        then putStrLn "Naciste un Lunes."
    else if resultado == 4
        then putStrLn "Naciste un Martes."
    else if resultado == 5
        then putStrLn "Naciste un Miercoles."
    else if resultado == 6
        then putStrLn "Naciste un Jueves."
    else
        putStrLn "No naciste."

main :: IO ()
main = do
    putStrLn "Ingrese su año de nacimiento:"
    a <- readLn
    putStrLn "Ingrese su mes de nacimiento:"
    m <- readLn
    putStrLn "Ingrese su día de nacimiento:"
    d <- readLn
    diaSemana a m d
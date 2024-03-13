import Data.Bits (And(And))

sumTotal x = if x == 0
    then 0
    else x + sumTotal (x - 1)


sumaTotalOpt :: (Eq t, Num t) => t -> t -> t
sumaTotalOpt x y = if x == 0
    then y
    else sumaTotalOpt (x - 1) (x + y)


-- crear lista recursiva
crearLista :: (Eq t, Num t) => t -> [t]
crearLista x = if x == 0
    then []
    else x : crearLista (x - 1)

--main
main :: IO ()
main = do
    print (sumTotal 10)
    print (sumaTotalOpt 10 0)
    print (crearLista 10)

    
import Data.Bits (And (And))
import Control.Monad.RWS.Class (MonadState(put))

sumTotal x =
  if x == 0
    then 0
    else x + sumTotal (x - 1)

sumaTotalOpt :: (Eq t, Num t) => t -> t -> t
sumaTotalOpt x y =
  if x == 0
    then y
    else sumaTotalOpt (x - 1) (x + y)

-- crear lista recursiva
crearLista x y =
  if x == 0
    then y
    else crearLista (x - 1) (z : y)
  where
    z = x - 1

duplicarLista :: [Int] -> [Int]
duplicarLista = map (* 2)

filterParesLista = filter (\x -> (mod x 2) == 0)

oksucc x = succ x

incrementarLista = map succ

sumarTresNumeros x y z = x + y + z

sumarYMostrar driver x y  = driver (show(x + y))

sumaYImprime = sumarYMostrar putStrLn 


combinar = incrementarLista . duplicarLista . filterParesLista

--pattern matching
--sealed classes 

printLuckNum 7 = "Lucky number!!"
printLuckNum 5 = "Lucky number!!"
printLuckNum x = "Not lucky number"

sumaTotalOpt1 :: (Eq t, Num t) => t -> t -> t
sumaTotalOpt1 0 y = y
sumaTotalOpt1 x y = sumaTotalOpt (x - 1) (x + y)

--deconstruccion
data Peso = PesoNKG Float | PesoNgramos Float

mostrarPeso :: Peso -> IO ()
mostrarPeso (PesoNgramos x) = putStrLn (show (x/1000))
mostrarPeso (PesoNKG x) = putStrLn (show x)



-- main
main :: IO ()
main = do
  print (sumTotal 10)
  print (sumaTotalOpt 10 0)

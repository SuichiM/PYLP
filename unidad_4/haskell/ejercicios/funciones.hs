module Funciones where

{- Funciones iniciales -}

-- 1. sucesor
sucesor :: Integer -> Integer
sucesor x = x + 1

pre :: Integer -> Integer
pre x = x - 1 

-- 2. doble 
doble :: Integer -> Integer
doble x = x+x


-- 3. Cuadruple de un numero
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))

-- 4. Numero par
isPar :: Integer -> Bool
isPar x = x `rem` 2 == 0 

-- 5. Devuelve mayor
mayor :: (Integer, Integer) -> Integer
mayor (x,y) = if x>=y then x else y

-- 6. Division tupla
--divisionTupla :: (Integer, Integer) -> Double
--divisionTupla (x,y) = fromInteger(x) / fromInteger(y)

factorial :: Integer -> Integer
factorial x = if (x==1) then 1 
                else
                    x*factorial(x-1)

factorial_b :: Integer -> Integer
factorial_b 0 = 1
factorial_b 1 = 1
factorial_b 2 = 2
factorial_b x = x * factorial_b(x-1)

factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = facAux(1, x, 1) 

facAux :: (Integer, Integer, Integer) -> Integer
facAux(it, base, total) = if(it>base) then total else facAux(it+1,base,total*it)


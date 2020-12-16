module Funciones where

{- funciones de lista -}

-- 1) SUCESOR
sucesor :: Integer -> Integer
sucesor(x) = x + 1
 
-- 2) DOBLE
doble :: Integer -> Integer
doble x = x + x

-- 3) CUADRUPLE
cuadruple :: Integer -> Integer
cuadruple(x) = doble(doble(x))

-- 4) ES PAR
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0 

-- 5) MAYOR
mayor :: (Integer, Integer) -> Integer
mayor (x,y) = if x >= y then x else y

-- 6) DIVISION
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y)

-- 7) DIVISION2
division2 :: (Integer, Integer) -> (Integer, Integer)
division2 (x,y) = (x `div` y, x `mod` y)

-- 8) FACTORIAL A
factorial_a :: Integer -> Integer
factorial_a x = if ( x == 1 ) then 1
                else x * factorial_a(x-1)

-- 9) FACTORIAL B
factorial_b :: Integer -> Integer
factorial_b 0 = 1
factorial_b x = x * factorial_b(x-1)

-- 10) FACTORIAL C
factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = factorialAux(1, x, 1) 

factorialAux :: (Integer, Integer, Integer) -> Integer
factorialAux(iteration, base, total) = if iteration > base then total
                              	       else factorialAux(iteration + 1, base, total * iteration)

-- 11) POTENCIA
potencia :: (Integer, Integer) -> Integer
potencia (base, 0) = 1
potencia (base, 1) = base
potencia (base, exponente) = base * potencia(base, exponente - 1)


-- 12) LONGITUD
longitud :: [Integer] -> Integer
longitud [] = 0
longitud (x:xs) = 1 + longitud(xs)

-- 13) SUMATORIA
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

-- 14) MAXIMO
maximo [] = 0
maximo (x:xs) = maximoAux(x, xs)

maximoAux (e, []) = e
maximoAux (e, x:xs) = if e > x then
			maximoAux(e, xs)
		      else
		      	maximoAux(x, xs)

-- 15) PUSH
push (e, []) = [e]
push (e, x:xs) = x:push(e, xs)


-- 16) CUSTOM FILTER
customFilter (f, []) = []
customFilter (f, x:xs) =  if f(x) == True then
                                x:customFilter(f, xs)
                          else
                                customFilter(f, xs)

-- 17) CUSTOM MAP
customMap (f,[]) = []
customMap (f,x:xs) = f(x) : customMap(f, xs)

-- 18) INDEX OF
indexOf (e, []) = -1
indexOf (e, x:xs) = indexOfAux(e, x:xs, 0)

indexOfAux (e, [], index) = -1
indexOfAux (e, x:xs, index) = if(e == x) then
                                        index
                                else
                                        indexOfAux(e, xs, index + 1)


-- 19) EXISTS
exists (e, []) = False
exists (e, x:xs) = if e == x then 
                	True
                   else
                      	exists(e, xs)

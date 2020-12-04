module Funciones where

{- Funciones simples -}

-- 1) Funcion que dado un entero devuelva el sucesor
sucesor :: Integer -> Integer
sucesor(x) = x + 1
 
-- 2) Función que devuelva el doble de un numero
doble :: Integer -> Integer
doble x = x + x

-- 3) Función que devuelve el cuadruple de un numero, utilizando composicion de funciones
cuadruple :: Integer -> Integer
cuadruple(x) = doble(doble(x))

-- 4) Función que devuelve un booleano indicando si un numero pasado como parámetro es par
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0 

-- 5) Funcion que tomado una tupla de numeros devuelva el mayor
mayor :: (Integer, Integer) -> Integer
mayor (x,y) = if x >= y then x else y

-- 6) Funcion que dada una tupla de enteros, devuelva la division de dichos numeros
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y)

-- 7) Funcion que dada una tupla de enteros devuelva una tupla con la division entera como primer miembro y el resto como segundo miembro de la tupla
division_mod :: (Integer, Integer) -> (Integer, Integer)
division_mod (x,y) = (x `div` y, x `mod` y)


{- Funciones condicionales o recursivas -}


-- 8) Función recursiva que devuelve el factorial de un numero
factorial :: Integer -> Integer
factorial x = if ( x == 1 ) then 
                        1
                else 
                        x * factorial(x-1)

-- 9) Función anterior aplicando ajuste de patrones
factorial_patrones :: Integer -> Integer
factorial_patrones 0 = 1
factorial_patrones x = x * factorial_patrones(x-1)

-- 10) Funcion anterior pero con recursion final
factorial_recursion :: Integer -> Integer
factorial_recursion 0 = 1
factorial_recursion x = factorial_aux(1, x, 1) 

factorial_aux :: (Integer, Integer, Integer) -> Integer
factorial_aux(iteration, base, total) = if iteration > base then 
                                            total
                              	   else 
                                            factorial_aux(iteration + 1, base, total * iteration)

-- 11) Funcion que dada una tupla (base, exponente) devuelva la potencia exponente de la base
potencia :: (Integer, Integer) -> Integer
potencia (base, 0) = 1
potencia (base, 1) = base
potencia (base, exponente) = base * potencia(base, exponente - 1)



{- Funciones de lista -}


-- 12) Funcion que dada una lista de elementos devuelva la longitud de dicha lista
longitud :: [Integer] -> Integer
longitud [] = 0
longitud (x:xs) = 1 + longitud(xs)

-- 13) Funcion que dada una lista de elementos devuelva la suma de los elementos de dicha lista
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

-- 14) Funcion que devuelve el Maximo elemento de una lista
maximo [] = 0
maximo (x:xs) = maximo_aux(x, xs)

maximo_aux (e, []) = e
maximo_aux (e, x:xs) = if e > x then
			      maximo_aux(e, xs)
		      else
		      	maximo_aux(x, xs)

-- 15) Funcion que dado una lista y un numero. devuelve la lista con el elemento insertado al final
push (e, []) = [e]
push (e, x:xs) = x:push(e, xs)


-- 16) Funcion que dada una lista, filtra los elementos de la lista segun un criterio dada en una funcion
customFilter (f, []) = []
customFilter (f, x:xs) =  if f(x) == True then
                                x:customFilter(f, xs)
                          else
                                customFilter(f, xs)

-- 17) Funcion que dada una funcion y una lista, aplique la funcion a todos los elementos de la lista
customMap (f,[]) = []
customMap (f,x:xs) = f(x) : customMap(f, xs)

-- 18) Funcion que pasada una un valor y una lista, devuelve la posicion en donde se encontro dicho elemento o -1 si no fue hallado
indexOf (e, []) = -1
indexOf (e, x:xs) = index_aux(e, x:xs, 0)

index_aux (e, [], index) = -1
index_aux (e, x:xs, index) = if(e == x) then
                                        index
                                else
                                        index_aux(e, xs, index + 1)


-- 19) Funcion que pasado un valor y una lista, devuelve Verdadero o Falso segun si el elemento existe en la lista
exists (e, []) = False
exists (e, x:xs) = if e == x then 
                	      True
                  else
                        exists(e, xs)

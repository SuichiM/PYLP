module Funciones where

{- Funciones Simples -}

-- 1. Escribir una funcion que dado un entero devuelva el sucesor.
sucesor :: Integer -> Integer
sucesor x = x + 1

-- 2. Escribir una función en Haskell que devuelva el doble de un numero.
doble :: Integer -> Integer
doble x = x+x

-- 3. Escribir una función que devuelva el cuadruple de un numero, utilizando composicion de funciones y la funcion del punto anterior.
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))

-- 4. Escribir una función que devuelva un booleano indicando si un numero pasado como parámetro es par.
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0

-- 5. Escribir una funcion que tomado una tupla de numeros devuelva el mayor.
mayor :: (Integer, Integer) -> Integer
mayor (x,y) = if x>=y then x else y 

-- 6. Escribir una funcion que dada una tupla de enteros, devuelva la division de dichos numeros
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y) 

-- 7. Escribir una funcion que dada una tupla de enteros devuelva una tupla con la division entera como primer miembro y el resto como segundo miembro de la tupla
divisionResto :: (Integer, Integer) -> (Integer, Integer)
divisionResto (x,y) = (x `div` y,x `rem` y) 


{- Funciones condicionales o recursivas -}

-- 8. Hacer una función recursiva que devuelva el factorial de un numero.
factorial :: Integer -> Integer
factorial x =   if (x==1) then 1 
                else
                    x*factorial(x-1)


-- 9. Modificar la función anterior aplicando ajuste de patrones
factorialPatrones :: Integer -> Integer
factorialPatrones 0 = 1
factorialPatrones 1 = 1
factorialPatrones x = x*factorial(x-1)

-- 10. Escribir la funcion anterior pero con recursion final
factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = facAux(1, x, 1) 

facAux :: (Integer, Integer, Integer) -> Integer
facAux(it, base, total) = if(it>base) then total else facAux(it+1,base,total*it)

-- 11. Escribir una funcion que dada una tupla (base, exponente) devuelva la potencia exponente de la base.
potencia :: (Integer, Integer) -> Double
potencia (0,y) = 0
potencia (x,0) = 1
potencia (x,y) =  fromInteger(x) ** fromInteger(y)




{- Funciones de lista -}

-- 12. Escribir una funcion que dada una lista de elementos devuelva la longitud de dicha lista. longitud
longitud :: [Int] -> Integer
longitud [] = 0
longitud (x:xs) = 1 + longitud(xs)


-- 13. Escribir una funcion que dada una lista de elementos devuelva la suma de los elementos de dicha lista. sumatoria
sumatoria :: [Integer] -> Integer
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

-- 14. Escribir una funcion que devuelva el Maximo elemento de una lista maximo
maximo :: [Int] -> Int
maximo [] = 0
maximo (x:xs) = if (x < maximo(xs)) 
                then maximo(xs)
                else x

-- 15. Escribir una funcion que dada una lista y un numero. devuelva la lista con el elemento insertado al final. push
push (a, []) = [a]
push (a, x:xs) = x:push(a, xs)


-- 16. Escribir una funcion que dada una lista, filtre los elementos de la lista segun un criterio dada en una funcion. customFilter
customFilter(f, []) = []
customFilter(f, x:xs) = if (f(x)) then
                            x : customFilter(f, xs)
                        else
                            customFilter(f, xs)


-- 17. Escribir una funcion que dada una funcion y una lista, aplique la funcion a todos los elementos de la lista. customMap
customMap (f,[]) = []
customMap (f,x:xs) = f(x) : customMap(f, xs)

-- 18. Escribir una funcion que pasada una un valor y una lista, devuelva la posicion en donde se encontro dicho elemento o -1 si no fue hallado. indexOf
indexOf (num, []) = -1
indexOf (num, x:xs) = indexOfAux(num, x:xs, 0)

indexOfAux (num, [], index) = -1
indexOfAux (num, x:xs, index) = if (num == x) 
                                then
                                    index
                                else
                                    indexOfAux(num, xs, index + 1)


-- 19. Escribir una funcion que pasada un valor y una lista, devuelva Verdadero o Falso segun si el elemento existe en la lista. exists
exists :: (Int, [Int]) -> Bool
exists (a,[]) = False
exists (a,x:xs) =   if (a == x)
                    then True
                    else exists(a,xs)
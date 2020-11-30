module FuncionesZakowicz where

{- Funciones simples -}

-- 1. Sucesor de un valor entero
sucesor :: Integer -> Integer
sucesor x = x + 1

pre :: Integer -> Integer
pre x = x - 1 

-- 2. Doble de un número
doble :: Integer -> Integer 
doble x = x*2 

-- 3. Cuádruple de un número, utilizando composición de funciones
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))

-- 4. Función booleana indicando si un numero es par
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0

-- 5. Devuelve el mayor de una tupla de números
mayor :: (Integer, Integer) -> Integer
mayor (x, y) = if x>=y then x else y

-- 6. Devuelve la división de una tupla de enteros
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y)

-- 7. Devolver una tupla [división entera, resto], dada una tupla de enteros
divEntero :: (Integer, Integer) -> (Integer, Integer)
divEntero (x,y) = (x `div` y, x `rem` y)

{- Funciones condicionales o recursivas -}

-- 8. Hacer una función recursiva que devuelva el factorial de un numero.
-- Recursión final (va de x hasta el caso base y luego empieza a devolver para atrás)
factorial_a :: Integer -> Integer
factorial_a x = if ( x == 1 ) then 1
                else
                  x * factorial_a(x-1)

-- 9. Modificar la función anterior aplicando ajuste de patrones.(Recursión final)
factorial_b :: Integer -> Integer
factorial_b 0 = 1
factorial_b x = x * factorial_b(x-1)

-- 10. Escribir la funcion anterior pero con una recursion no final.
-- Recursión no final (va desde es el caso base hasta x)
factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = factorialAux(1, x, 1) 

factorialAux :: (Integer, Integer, Integer) -> Integer
factorialAux(it, base, tot) = if it > base then tot
                              else
                                factorialAux(it+1, base, tot*it)

-- 11. Escribir una funcion que dada una tupla `(base, exponente)` devuelva la potencia exponente de la base.
-- 11.1
potencia_a :: (Integer, Integer) -> Integer
potencia_a (b, e) = if (e == 0) then 1
                  else b * potencia_a(b, e-1)

-- 11.2
potencia_b :: (Integer, Integer) -> Integer
potencia_b (b, 0) = 1
potencia_b (b, e) = b * potencia_a(b, e-1)

-- 11.3 
potencia_c :: (Integer, Integer) -> Integer
potencia_c (b, 0) = 1
potencia_c (b, e) = potenciaAux(1, b, e)

potenciaAux :: (Integer, Integer, Integer) -> Integer
potenciaAux(it, base, exp) = if it >= exp then base
                              else
                               base * potenciaAux(it+1, base, exp)

{- Funciones de lista -}      

 -- 12. Escribir una funcion que dada una lista de elementos devuelva la longitud de dicha lista. `longitud`
longitud :: [Integer] -> Integer
longitud [] = 0
longitud (x:xs) = 1 + longitud (xs)

-- 13. Escribir una funcion que dada una lista de elementos devuelva la suma de los elementos de dicha lista. `sumatoria`
sumatoria :: [Integer] -> Integer
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

-- 14. Escribir una funcion que devuelva el Maximo elemento de una lista `maximo`
-- Para obtener el máximo de una lista se utiliza la función maximum' 
maximum' :: [Integer] -> Integer
maximum'[] = 0
maximum'[x] = x
maximum'(x:xs) = x `max` (maximum' xs)
-- maximum: máximo elemento de la lista xs
-- max: máximo entre x e y

-- 15. Escribir una funcion que dada una lista y un numero. devuelva la lista con el elemento insertado al final. `push`
push :: (Integer, [Integer]) -> [Integer]
push (e, []) = [e]
push (e, x:xs) = x : push(e, xs)

-- 16. Escribir una funcion que dada una lista, filtre los elementos de la lista segun un criterio dada en una funcion. `customFilter`
customFilter (f, []) = []
customFilter (f, x:xs) = if (f(x) == True) then
                            x : customFilter(f, xs)
                          else
                            customFilter(f, xs)

-- 17. Escribir una funcion que dada una funcion y una lista, aplique la funcion a todos los elementos de la lista. `customMap`   
-- Ej: customMap(doble, [2,3,4])
customMap (f, []) = []
customMap (f, x:xs) =f(x): customMap(f, xs)    

-- 18. Escribir una funcion que pasada una un valor y una lista, devuelva la posicion en donde se encontro dicho elemento o -1 si no fue hallado. `indexOf`
-- i = posición de cada elemento de la lista.
indexOf (e, []) = -1
indexOf (e, x:xs) = indexOfAux(e, x:xs, 0)

indexOfAux (e, [], i) = -1
indexOfAux (e, x:xs, i) = if (e == x) then i
                       else 
                         indexOfAux (e, xs, i + 1)

-- 19. Escribir una funcion que pasada un valor y una lista, devuelva Verdadero o Falso segun si el elemento existe en la lista. `exists`
exists (e, []) = False
exists (e, x:xs) = if (e == x) then True
                    else 
                      exists (e, xs)
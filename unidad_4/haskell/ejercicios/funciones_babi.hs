Module Funciones where

-- 1. Escribir una funcion que dado un entero devuelva el sucesor.
sucesor :: Integer -> Integer
sucesor(x) = x + 1

-- 2. Escribir una función en Haskell que devuelva el doble de un numero.
doble :: Integer -> Integer
doble x = x + x

-- 3. Escribir una función que devuelva el cuadruple de un numero, utilizando composicion de funciones y la funcion del punto anterior.
cuadruple :: Integer -> Integer
cuadruple(x) = doble(x) + doble(x)

-- 4. Escribir una función que devuelva un booleano indicando si un numero pasado como parámetro es par.
es_par :: Integer -> Bool
es_par x = x `mod` 2 == 0 

-- 5. Escribir una funcion que tomado una tupla de numeros devuelva el mayor.
mayor :: (Integer, Integer) -> Integer
mayor (x, y) = if x < y then y else x

-- 6. Escribir una funcion que dada una tupla de enteros, devuelva la division de dichos numeros
dividir :: (Integer, Integer) -> Double
dividir (x, y) = fromInteger(x) / fromInteger(y)

-- 7. Escribir una funcion que dada una tupla de enteros devuelva una tupla con la division entera como primer miembro y el resto como segundo miembro de la tupla
dividir_resto :: (Integer, Integer) -> (Integer, Integer)
dividir_resto (x, y) = (x `div` y, x `mod` y)

-- 8. Hacer una función recursiva que devuelva el factorial de un numero.
factorial :: Integer -> Integer
factorial x = if ( x == 1 ) then 1 else x * factorial(x - 1)

-- 9. Modificar la función anterior aplicando ajuste de patrones.
factorial_b :: Integer -> Integer
factorial_b 0 = 1
factorial_b x = x * factorial_b(x - 1)

-- 10. Escribir la funcion anterior pero con recursion final
factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = x * factorial_final(1, x, 1) 

factorial_final :: (Integer, Integer, Integer) -> Integer
factorial_final(iter, base, total) = if(iter > base) then total else factorial_final(iter + 1, base, total * iter)

-- 11. Escribir una funcion que dada una tupla (base, exponente) devuelva la potencia exponente de la base.
potencia :: (Integer, Integer) -> Integer
potencia (base, 0) = 1
potencia (base, 1) = base
potencia (base, exponente) = base * potencia(base, exp - 1)

-- 12. Escribir una funcion que dada una lista de elementos devuelva la longitud de dicha lista. `longitud`
longitud :: [Integer] -> Integer
longitud [] = 0
longitud ( x : xs ) = 1 + longitud( xs )

-- 13. Escribir una funcion que dada una lista de elementos devuelva la suma de los elementos de dicha lista. `sumatoria`
sumatoria [] = 0
sumatoria ( x : xs ) = x + sumatoria( xs )

-- 14. Escribir una funcion que devuelva el Maximo elemento de una lista `maximo`
maximo [] = "Lista vacia"
maximo ( x : xs ) = maximo_b( x, xs )

maximo_b ( elem, [] ) = e
maximo_b ( elem, x : xs ) = if elem > x then maximo_b( elem, xs ) else maximo_b( x, xs )

-- 15. Escribir una funcion que dada una lista y un numero. devuelva la lista con el elemento insertado al final. `push`
push ( elem, [] ) = [e]
push ( elem, x : xs ) = x : push( elem, xs )

-- 16. Escribir una funcion que dada una lista, filtre los elementos de la lista segun un criterio dada en una funcion. `customFilter`
customFilter ( f, [] ) = []
customFilter ( f, x : xs ) =  if f( x ) == True then x:customFilter( f, xs ) else customFilter( f, xs )

-- 17. Escribir una funcion que dada una funcion y una lista, aplique la funcion a todos los elementos de la lista. `customMap`
customMap ( f, [] ) = []
customMap ( f, x : xs ) = f( x ) : customMap( f, xs )

-- 18. Escribir una funcion que pasada una un valor y una lista, devuelva la posicion en donde se encontro dicho elemento o -1 si no fue hallado. `indexOf`
indexOf ( elem, [] ) = -1
indexOf ( elem, x : xs ) = index_aux( elem, x : xs, 0 )

index_b ( elem, [], index ) = -1
index_b ( elem, x : xs, index ) = if(elem == x) then index else index_b(elem, xs, index + 1)

-- 19. Escribir una funcion que pasada un valor y una lista, devuelva Verdadero o Falso segun si el elemento existe en la lista. `exists`
exists ( elem, [] ) = False
exists ( elem, x : xs ) = if elem == x then True else exists( elem, xs )
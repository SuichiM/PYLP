#include <omp.h>
#include <iostream>

#define NH 4
#define CINCO 5 

int main (){
    int hilo, producto, total=0, lng=NH*CINCO;
    int vectorGlobal1[lng], vectorGlobal2[lng];


    //Cargamos los vectores
    for (int i = 0; i < lng; i++){
        vectorGlobal1[i] = i;
        vectorGlobal2[i] = (lng-1) - i;

    }

    //Imprimimos los vectores
    printf("Vector global 1:\n");
    for (int i = 0 ; i < lng; i++)
    {
        printf(" %d -",vectorGlobal1[i]);
    }
    printf("\n\n");

    printf("Vector global 2:\n");
    for (int i = 0 ; i < lng; i++)
    {
        printf(" %d -",vectorGlobal2[i]);
    }
    printf("\n\n");

    /*RESULTADO EN MI CONSOLA
        Vector global 1:
        0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 -

        Vector global 2:
        19 - 18 - 17 - 16 - 15 - 14 - 13 - 12 - 11 - 10 - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 - 0 -
    */


    //Seteamos la cantidad de hilos
    omp_set_num_threads(NH);

    #pragma omp parallel private(hilo, producto), firstprivate(vectorGlobal1, vectorGlobal2, lng) reduction(+:total)
    {
        hilo = omp_get_thread_num();
        producto = 0;

        #pragma omp for schedule(auto) //Se puede utilizar cualquiera los planificadores "auto" o "static" (static indicando el numero de hilos), ya que con estos planificadores nos aseguramos de que los hilos realicen una cantidad de trabajo equilibrada, y no que un hilo realice mas trabajo que otro
        for (int i=0; i<lng; i++){
            #pragma omp atomic
            producto+=vectorGlobal1[i]*vectorGlobal2[i];
        }

        //atomic a diferencia de critical hace que la actualizacion de la memoria en la siguiente instrucción sea atómica (solo sirve para escritura/lectura en memoria). Critical, en cambio, hace que el siguiente bloque se ejecute por un solo hilo a la vez.
        #pragma omp atomic
        total+=producto;
        
        printf("Resultado parcial del proceso %d es: %d \n", hilo, total);

    }

    printf("\nProducto escalar: %d\n\n",total);

    /*RESULTADO DE MI CONSOLA
        Vector global 1:
        0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 -

        Vector global 2:
        19 - 18 - 17 - 16 - 15 - 14 - 13 - 12 - 11 - 10 - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 - 0 -

        Resultado parcial del proceso 0 es: 160 
        Resultado parcial del proceso 2 es: 410
        Resultado parcial del proceso 1 es: 410
        Resultado parcial del proceso 3 es: 160

        Producto escalar: 1140
    */
}


#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, lng, num, cantMultiplos, maxGlobal;

    MPI_Init(&argc, &argv);  //se inicia la comunicación paralela entre procesos

    MPI_Comm_size(MPI_COMM_WORLD, &size); //se obtiene en "size" el numero de procesos del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //se obtiene en "rank" el identificador del proceso segun el comunicador MPI_COMM_WORLD

    num = 5;
    maxGlobal = 0;
    cantMultiplos = 0;
    lng = size * num;
    int vectorPrincipal[lng];

    if (rank == 0){// se carga el vector en el proceso 0


        for (int i = 0; i < lng; i++){

            vectorPrincipal[i] = rand() % 100;

        }

        // imprimir el vector
        printf("Vector cargado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -", vectorPrincipal[i]);
        }

        printf("\n\n");
    }

    // Se envia el vector cargado a todos los procesos
    MPI_Bcast(
        &vectorPrincipal[0],   // Dirección inicial del buffer desde donde se envia
        lng,                // Número de elementos en el buffer
        MPI_INT,            // Tipo de dato de los elementos del buffer
		0,                  // Rango del proceso desde donde se transmitira
        MPI_COMM_WORLD      // Por que comunicador se hace la transmisión
    );
    
    // operacion a realizar en cada proceso
    // se contabiliza todos los elementos del vector, que sean multiplo del elemento en la posicion "rank"
    for (int i = 0; i < lng; i++){
        if (vectorPrincipal[i] % vectorPrincipal[rank] == 0){
            cantMultiplos ++;
        }
    }

    // Cada proceso informa su cantidad de numeros multiplos encontrados
    printf("Soy proceso %d; encontre %d multiplos del elemento %d\n", rank, cantMultiplos, vectorPrincipal[rank]);


    //Se obtiene en el proceso 0 la cantidad maxima de multiplos encontrados por un proceso
    MPI_Reduce(
            &cantMultiplos,   //Dirección inicial del buffer en envío.
            &maxGlobal,   //Dirección inicial del buffer de recepción, útil únicamente para el proceso raíz.
            1,            //Número de elementos que se va a enviar
            MPI_INT,      //Tipo de datos de los elementos del buffer de envío
            MPI_MAX,      //Operación de reducción
            0,            // Rango del proceso raíz - receptor
            MPI_COMM_WORLD //Comunicador por el que se realiza la comunicación.
            );


    if (rank == 0) { // El proceso 0 informa el resultado

        printf("La mayor cantidad de multiplos obtenidos por un proceso es: %d \n", maxGlobal);

    }

    MPI_Finalize();//se finaliza la comunicación paralela entre procesos

    /* ejemplo de ejecucion:

        Vector cargado: 
        83 - 86 - 77 - 15 - 93 - 35 - 86 - 92 - 49 - 21 - 62 - 27 - 90 - 59 - 63 - 26 - 40 - 26 - 72 - 36 - 11 - 68 - 67 - 29 - 82 - 30 - 62 - 23 - 67 - 35 -

        Soy proceso 0; encontre 1 multiplos del elemento 83
        Soy proceso 2; encontre 1 multiplos del elemento 77
        Soy proceso 1; encontre 2 multiplos del elemento 86
        Soy proceso 5; encontre 2 multiplos del elemento 35
        Soy proceso 4; encontre 1 multiplos del elemento 93
        Soy proceso 3; encontre 3 multiplos del elemento 15
        La mayor cantidad de multiplos obtenidos por un proceso es: 3 
    */


    return 0;
}
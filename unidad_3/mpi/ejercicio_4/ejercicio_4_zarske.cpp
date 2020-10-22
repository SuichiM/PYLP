#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, lng, sumaLocal, num, sumaTotal;

    MPI_Init(&argc, &argv);  //se inicia la comunicación paralela entre procesos

    MPI_Comm_size(MPI_COMM_WORLD, &size); //se obtiene en "size" el numero de procesos del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //se obtiene en "rank" el identificador del proceso segun el comunicador MPI_COMM_WORLD

    num = 5;
    sumaLocal = 0;
    sumaTotal = 0;
    lng = size * num;
    int vectorPrincipalUno[lng];
    int vectorPrincipalDos[lng];
    int vectorLocalUno[num];
    int vectorLocalDos[num];

    if (rank == 0){// se cargan los vectores en el proceso 0


        for (int i = 0; i < lng; i++){

            vectorPrincipalUno[i] = rand() % 100;
            vectorPrincipalDos[i] = rand() % 100;

        }

        // imprimir los vectores generados
        printf("Primer vector cargado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -", vectorPrincipalUno[i]);
        }
        printf("\n");
        printf("Segundo vector cargado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -", vectorPrincipalDos[i]);
        }

        printf("\n\n");
    }

    // distribuir el vector Uno con MPI_Scatter
    MPI_Scatter(
      &vectorPrincipalUno[0],    //Dirección inicial del buffer de salida
      num,                       //Número de elementos que se envía a cada proceso del comunicador
      MPI_INT,                   //Tipo de dato que se va a enviar
      &vectorLocalUno[0],        //Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
      num,                       //Número de elementos que espera recibir cada proceso
      MPI_INT,                   //Tipo de datos de los elementos a recibir 
      0,                         //Rango del proceso que hace el envio
      MPI_COMM_WORLD             //Comunicador por el que realizar la comunicación.
      );

    // distribuir el vector Dos con MPI_Scatter
    MPI_Scatter(
      &vectorPrincipalDos[0],  //Dirección inicial del buffer de salida
      num,                     //Número de elementos que se envía a cada proceso del comunicador
      MPI_INT,                 //Tipo de dato que se va a enviar
      &vectorLocalDos[0],      //Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
      num,                     //Número de elementos que espera recibir cada proceso
      MPI_INT,                 //Tipo de datos de los elementos a recibir 
      0,                       //Rango del proceso que hace el envio
      MPI_COMM_WORLD           //Comunicador por el que realizar la comunicación.
      );

    // operar los vectores locales
    for (int i = 0; i < num; i++){

        sumaLocal += vectorLocalDos[i] * vectorLocalUno[i];
        
    }

    // se reduce (por suma) en la variable sumaTotal del proceso 0 el resultado de producto escalar segun la sumaLocal de los vectores
    MPI_Reduce(
            &sumaLocal,   //Dirección inicial del buffer en envío.
            &sumaTotal,   //Dirección inicial del buffer de recepción, útil únicamente para el proceso raíz.
            1,            //Número de elementos que se va a enviar
            MPI_INT,      //Tipo de datos de los elementos del buffer de envío
            MPI_SUM,      //Operación de reducción
            0,            // Rango del proceso raíz - receptor
            MPI_COMM_WORLD //Comunicador por el que se realiza la comunicación.
            );

    //
    if (rank == 0) { // El proceso 0 informa el resultado

        printf("\nEl resultado del producto escalar es: %d\n", sumaTotal);


    }

    MPI_Finalize();//se finaliza la comunicación paralela entre procesos
    

    /* Prueba de funcionamiento
    
        root@0b7ece231d98:/home/mpi/ejercicio_4# mpirun --allow-run-as-root --oversubscribe -np 5 ej4_zarske.obj 
        
        Primer vector cargado: 
        83 - 77 - 93 - 86 - 49 - 62 - 90 - 63 - 40 - 72 - 11 - 67 - 82 - 62 - 67 - 29 - 22 - 69 - 93 - 11 - 29 - 21 - 84 - 98 - 15 -
        Segundo vector cargado: 
        86 - 15 - 35 - 92 - 21 - 27 - 59 - 26 - 26 - 36 - 68 - 29 - 30 - 23 - 35 - 2 - 58 - 67 - 56 - 42 - 73 - 19 - 37 - 24 - 70 -


        El resultado del producto escalar es: 62318
    
    */


    return 0;
} 
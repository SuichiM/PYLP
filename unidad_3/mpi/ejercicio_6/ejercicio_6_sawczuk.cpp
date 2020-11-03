#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rango, size, lng;
    int multiplos[2];       //posicion 0 el rango del proceso y posicion 1 el numero de multiplos que tiene
    int resMultiplos[2];    //posicion 0 el rango del proceso y posicion 1 el numero de multiplos que tiene
    multiplos[0] = 4535;
    multiplos[1] = 0;
    resMultiplos[0] = 5335;
    resMultiplos[1] = 0;
    MPI_Init(&argc, &argv); //Inicializamos la estructura de comunicación paralela entre procesos

    MPI_Comm_rank(MPI_COMM_WORLD, &rango); //Obtenemos (en rango) el rango del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_size(MPI_COMM_WORLD, &size); //Obtenemos (en size) el tamaño del comunicador MPI_COMM_WORLD

    /* ANALISIS
        Vector global:          1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -

        Multiplos del Proceso 0 (calcula el multiplo de 1): todos

        Multiplos del Proceso 1 (calcula el multiplo de 2): 2, 4, 6, 8, 10, 12, 14, 16, 18, 20
        
        Multiplos del Proceso 2 (calcula el multiplo de 3): 3, 6, 9, 12, 15, 18

        Multiplos del Proceso 3 (calcula el multiplo de 4): 4, 8, 14, 16, 20

        El proceso que mas multiplos tiene es el 0 porque 1 es multiplo de todos los numeros enteros

    */

    //Definimos el vector y su tamaño
    lng = size * 5;

    int vectorGlobal[lng];


    //El proceso 0 carga del vector
    if (rango == 0){
        for (int i = 0; i < lng; i++){
            vectorGlobal[i] = i+1;

        }
        //Imprimo el vector global
        printf("Vector Global \n");
        for (int i = 0; i < lng; i++){
            printf("%d - ",vectorGlobal[i]);
        }
        printf("\n");  
        /*
            Vector Global
            1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 - 
        */

    }

    //Se envia el vector global a todos los procesos
    MPI_Bcast(
        &vectorGlobal[0],   //La variable que se transmite
        lng,                //Tamaño de lo que se envia
        MPI_INT,            //Tipo de datos
		0,                  //Rango del proceso que transmitira
        MPI_COMM_WORLD      //Por cual comunicador se hace la transmisión
    );




    //Imprimo el vector que recibió cada proceso
    printf("Soy el proceso proceso %d y recibí este vector: \n",rango);
    for (int i = 0; i < lng; i++){
        printf("%d - ",vectorGlobal[i]);
    }
    printf("\n"); 

    /*
        Soy el proceso proceso 0 y recibí este vector:
        1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
        Soy el proceso proceso 1 y recibí este vector:
        1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
        Soy el proceso proceso 2 y recibí este vector:
        1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
        Soy el proceso proceso 3 y recibí este vector:
        1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
    */

    //Contamos los multiplos de la posicion del vector segun el rango del vector
    for (int i = 0; i < lng; i++){
        if (vectorGlobal[i] % vectorGlobal[rango] == 0){
            multiplos[0] = rango;
            multiplos[1]++;
        }
    }

    //Imprimo la cantidad de multiplos
    printf("Multiplos del elemento en la posicion %d: %d\n", rango, multiplos[1]);
    /*
        Multiplos del elemento en la posicion 0 : 20
        Multiplos del elemento en la posicion 1 : 10
        Multiplos del elemento en la posicion 2 : 6
        Multiplos del elemento en la posicion 3 : 5
    */

    //Mandamos la cantidad de multiplos para que MPI_Reduce elija el que mas multiplos tuvo
    MPI_Reduce(
        &multiplos[1],          //Lo que envio 
        resMultiplos,           //Donde lo recibo
        1,                      //Tamaño de lo que envio
        MPI_INT,                //Tipo de lo que se envia (reduce)
        MPI_MAX,                //Operacion que se realiza
        0,                      //Proceso receptor
        MPI_COMM_WORLD          //Comunicador
    );

    //Imprimimos en el proceso 0 cual fue el que mas multiplos
    if (rango == 0){
        printf("El proceso que mas multiplos obtuvo fue %d con %d múltiplos\n", resMultiplos[1], resMultiplos[0]);
    }



    /* IMPRESION EN MI COSOLA:
            Vector Global
            1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
            Soy el proceso proceso 0 y recibí este vector:
            1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
            Multiplos del elemento en la posicion 0: 20
            El proceso que mas multiplos obtuvo fue 0 con 20 múltiplos
            Soy el proceso proceso 1 y recibí este vector:
            1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
            Multiplos del elemento en la posicion 1: 10
            Soy el proceso proceso 2 y recibí este vector:
            1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
            Multiplos del elemento en la posicion 2: 6
            Soy el proceso proceso 3 y recibí este vector:
            1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
            Multiplos del elemento en la posicion 3: 5
    */

    MPI_Finalize(); //Finalizamos la estructura de comunicación paralela entre procesos
}
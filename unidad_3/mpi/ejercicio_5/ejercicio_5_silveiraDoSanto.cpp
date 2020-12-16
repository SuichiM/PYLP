#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, n, lng, sumaLocal, sumaTotal;
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    n = 5;
    sumaLocal =0;
    sumaTotal=  0;
    lng = size*5;

    int vector[lng];
    int vectorLocal[n];

    if(rank == 0) {

        for(int i = 0; i < lng ; i++){
            vector[i] = i;
        }
        printf("Vector Global: \n");
        for(int i = 0; i<lng ; i++){
            printf("%d - ", vector[i]);
        }
        printf("\n");
    }

    MPI_Scatter(
        &vector[0],    //Dirección inicial del buffer de salida
        n,                       //Número de elementos que se envía a cada proceso del comunicador
        MPI_INT,                   //Tipo de dato que se va a enviar
        &vectorLocal[0],        //Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
        n,                       //Número de elementos que espera recibir cada proceso
        MPI_INT,                   //Tipo de datos de los elementos a recibir 
        0,                         //Rango del proceso que hace el envio
        MPI_COMM_WORLD             //Comunicador por el que realizar la comunicación.
    );

    // operar con los vectores locales
    for (int i = 0; i < n; i++){

        if((vectorLocal[i] % (rank+2) ) == 0){
            vectorLocal[i] = 1; 
        }else {
            vectorLocal[i] = 0;
        }
        
    }

    //Se unen los vectores locales en el proceso 0 con MPI_Gather
    MPI_Gather(
        &vectorLocal[0],         // Dirección inicial del buffer de envío
        5,                       // Número de elementos que va a enviar cada proceso individualmente
        MPI_INT,                 // Tipo de dato de cada elemento del buffer de envío
        &vector[0],     // Dirección inicial del buffer de recepción (útil solamente para el proceso raíz).
        5,                       // Número de elementos que se espera recibir de cada uno de los procesos
        MPI_INT,                 // Tipo de dato que se espera recibir en el buffer de entrada
        0,                       // Rango del proceso raíz (el proceso receptor)
        MPI_COMM_WORLD           // Comunicador por el que se realiza la transferencia de datos
    );

    
    if (rank == 0) { // El proceso 0 informa el resultado

        printf("Resultado del vector transformado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -",vector[i]); 
        }
        printf("\n");
    }


    MPI_Finalize();
    
    return 0;
}
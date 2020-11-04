#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, n, lng, cantidadMult ,maximo;
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
    
    cantidadMult=0;
    maximo= 0;
    n = 5;
    lng = size*5;

    int v1[lng];

    if(rank == 0) {

        for(int i = 0; i < lng ; i++){
            v1[i] = i+1;
        }
        printf("Vector Global: \n");
        for(int i = 0; i<lng ; i++){
            printf("%d - ", v1[i]);
        }
        printf("\n");
    }

    MPI_Bcast(
        &v1[0],             //La variable que se transmite
        lng,                //Tamaño de lo que se envia
        MPI_INT,            //Tipo de datos
		0,                  //Rango del proceso que transmitira
        MPI_COMM_WORLD      //Por cual comunicador se hace la transmisión
    );


    for (int i = 0; i < lng; i++){

        if((v1[i] % v1[rank]) == 0){
            cantidadMult += 1 ;
        }
    }


    printf("En el proceso %d en la posicion [ %d ] tiene %d multiplos en el Vector Global\n", rank, v1[rank] ,cantidadMult); 



    MPI_Reduce(
        &cantidadMult, 
        &maximo, 
        1, 
        MPI_INT, 
        MPI_MAX, 
        0, 
        MPI_COMM_WORLD
    );

    if(rank == 0){
        printf("La mayor cantidad de multiplos obtenida es %d \n", maximo);
    }

    MPI_Finalize();
    
    return 0;
}
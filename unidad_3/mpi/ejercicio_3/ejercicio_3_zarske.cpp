  
#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, buzon;
    MPI_Status estado;
 
    MPI_Init(&argc, &argv); //se inicia la comunicación paralela entre procesos

    MPI_Comm_size(MPI_COMM_WORLD, &size);  //se obtiene en "size" el numero de procesos del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  //se obtiene en "rank" el identificador del proceso segun el comunicador MPI_COMM_WORLD

    if(rank == 0){ //El proceso con ID 0, envia un msj al proceso 2

        MPI_Send(
                    &rank, // proceso que envia
                    1,     // tamaño del vector a enviar
                    MPI_INT, // tipo de dato que se envia
                    rank+1,  // proceso que recibe
                    0,       //etiqueta
                    MPI_COMM_WORLD  // comunicador por donde se envia el msj
                    );

    }else{
        if(rank != size-1){ //Los procesos (exepto el de ID 0 y ID nSize) reciben msj del proceso n-1, y envia msj al proceso n+1

            MPI_Recv(
                &buzon, // referencia al vector donde se almacena lo recibido
                1,      // tamaño del vector a recibir
                MPI_INT, // tipo de dato que se recibe
                rank-1,  // proceso desde el cual se recibe el msj
                0,       //etiqueta
                MPI_COMM_WORLD, // comunicador por donde se recibe el msj
                &estado // informacion sobre el estado de la recepcion (si ocurrio un error)
                );

            MPI_Send(
                    &rank, // proceso que envia
                    1,     // tamaño del vector a enviar
                    MPI_INT, // tipo de dato que se envia
                    rank+1,  // proceso que recibe
                    0,       //etiqueta
                    MPI_COMM_WORLD  // comunicador por donde se envia el msj
                    );

            printf("Soy el proceso %d y he recibido el mensaje: %d\n", rank, buzon);

        }else{ // El proceso (ultimo) con ID mas alto, solo recibe un msj

            MPI_Recv(
                &buzon, // referencia al vector donde se almacena lo recibido
                1,      // tamaño del vector a recibir
                MPI_INT, // tipo de dato que se recibe
                rank-1,  // proceso desde el cual se recibe el msj
                0,       //etiqueta
                MPI_COMM_WORLD, // comunicador por donde se recibe el msj
                &estado // informacion sobre el estado de la recepcion (si ocurrio un error)
                );

            printf("Soy el proceso %d y he recibido el mensaje: %d\n", rank, buzon);

        }
    }
 

 
    MPI_Finalize(); //se finaliza la comunicación paralela entre procesos
    
    return 0;
}
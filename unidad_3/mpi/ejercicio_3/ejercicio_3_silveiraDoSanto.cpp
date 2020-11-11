#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, mensaje;
    MPI_Status estado;

    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 
    cout<<"¡Hola Mundo desde el proceso "<<rank<<" de "<<size<<" que somos!"<<endl;
 
    if(rank == 0){
        MPI_Send(
            &rank, // que mando
            1, // tamanio de lo que envio
            MPI_INT, //tipo de dato de lo que envio
            rank+1, // identificador del destino
            0, // etiqueta
            MPI_COMM_WORLD // comunicador
        );
    }else{
        MPI_Recv(
            &mensaje, //donde se almacena lo recibido
            1, //tamanio de lo recibido
            MPI_INT, //ripo de dato de lo recibido
            rank-1, //de quien se espera el msj
            0, //etiqueta
            MPI_COMM_WORLD, //comunicador
            &estado //informacion
        );  
        printf("Soy el proceso %d y he recibido %d \n", rank, mensaje);

        if(rank < size - 1){
            MPI_Send(
                &rank, // que mando
                1, // tamanio de lo que envio
                MPI_INT, //tipo de dato de lo que envio
                rank+1, // identificador del destino
                0, // etiqueta
                MPI_COMM_WORLD // comunicador
            );
        }
    }

    MPI_Finalize();
    
    return 0;
}
// El programa ejecuta una serie de procesos en paralelo
// que envía y recibe mensajes. El mensaje será el identificador
// del proceso que envía el mensaje.
#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank,id,size; 
    MPI_Status status; 

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(rank == 0)
        MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    else
        MPI_Recv(&id,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
    if(rank < size-1)
        MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);

    //Imprime de forma continua, dificulta la lectura del resultado.
    //printf("Soy el Proceso %d y he recibido %d", rank, id); 
    if(rank == 0)
        cout<<"Soy el proceso "<<rank<<" y no tengo antecesor. "<<endl;
    else
        cout<<"Soy el proceso "<<rank<<" y he recibido "<<id<<"."<<endl;
    MPI_Finalize();
    return 0;
}

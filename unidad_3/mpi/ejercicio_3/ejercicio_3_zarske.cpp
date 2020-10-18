  
#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, buzon;
    MPI_Status estado;
 
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    if(rank == 0){

        MPI_Send(&rank, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);

    }else{
        if(rank != size-1){

            MPI_Recv(&buzon, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &estado);

            MPI_Send(&rank, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);

            printf("Soy el proceso %d y he recibido el mensaje: %d\n", rank, buzon);

        }else{

            MPI_Recv(&buzon, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &estado);

            printf("Soy el proceso %d y he recibido el mensaje: %d\n", rank, buzon);

        }
    }
 

 
    MPI_Finalize();
    
    return 0;
}
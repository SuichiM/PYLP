#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){

    int rank, size, recibido;
    MPI_Status estado;

    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    if(rank == 0 ){
        cout << "Soy el proceso " << rank << " y envio mi PID al proceso "<< rank+1 << endl;
        MPI_Send(&rank, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);      
    }else{
        MPI_Recv(&recibido, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &estado);
        if(rank < size-1)
            MPI_Send(&rank, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        cout << "Soy el proceso "<< rank << " y he recibido "<< recibido << endl;
    }    
    
    MPI_Finalize();
    return 0;
    
}
#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv); // inicia el entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // obtiene la cantidad de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // obtiene el ID del proceso en el comunicador global
 
    cout<<"Hola MPI desde el proceso "<<rank<<" de "<<size<<" que somos en el comunicador!"<<endl;
 
    MPI_Finalize(); // finaliza la comunicación paralela entre los procesos

    return 0;
}
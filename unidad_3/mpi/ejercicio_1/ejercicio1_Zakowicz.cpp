// El programa imprime la cantidad de procesos lanzados
// y su identificador.

#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size;
 
    MPI_Init(&argc, &argv); // Inicializa el entorno de ejecución MPI.
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Determina el número de procesos en el comunicador global.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Determina el id de proceso en el comunicador global.
 
    cout<<"Proceso "<<rank<<" de "<<size<<" que somos."<<endl;
 
    MPI_Finalize(); // Finaliza el entorno de ejecución MPI.    
    return 0;
}
#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv); // inicia el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // obtiene el ID del proceso en el comunicador global
    
    if (rank % 2 == 0) { // si el resto de la division es 0 entonces es divisible por 2, osea es par
        cout<<"soy el proceso: "<<rank<<" un proceso par"<<endl;
    } else {
        cout<<"soy el proceso: "<<rank<<" un proceso impar"<<endl;
    }

 
    MPI_Finalize(); // finaliza la comunicación paralela entre los procesos

    return 0;
}
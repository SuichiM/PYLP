#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
    
    int rank;
    
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
    
    if (rank % 2 == 0) //Si el identificador del proceso es divisible por 2 es par
        cout << "soy el proceso " << rank <<" un proceso par" << endl;
    else
        cout << "soy el proceso " << rank << " un proceso impar" << endl;

    MPI_Finalize();
    
    return 0;
    
}
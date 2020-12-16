#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, mensaje;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size); //obtengo la cantidad de procesos totales
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //obtengo el rango del proceso

    //leo el mensaje que este en cola, siempre y cuando no sea el primer proceso, que no tiene mensaje en espera
    if (rank != 0)
    {
        //Si no soy el proceso 0, leo el mensaje que esta en cola.
        MPI_Recv(&mensaje, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        cout << "Soy el proceso " << rank << " y he recibido " << mensaje << endl;
    }

    //Si existe un proceso proximo, envio un mensaje
    if (rank + 1 < size)
    {
        //Envio un mensaje a el proximo proceso
        MPI_Send(&rank, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
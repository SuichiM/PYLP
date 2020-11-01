#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank;

    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    //se define que el proceso 0 no es impar ni par, por ello se omite la impresion del mensaje en ese proceso
    if (rank != 0)
    {

        if (rank % 2 == 0)
        {
            cout << "soy el proceso: " << rank << " un proceso par" << endl;
        }
        else
        {
            cout << "soy el proceso: " << rank << " un proceso impar" << endl;
        }
    }

    // Terminamos la ejecucion de los procesos, despues de esto solo existira
    // la hebra 0
    // ¡Ojo! Esto no significa que los demas procesos no ejecuten el resto
    // de codigo despues de "Finalize", es conveniente asegurarnos con una
    // condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();

    return 0;
}
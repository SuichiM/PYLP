#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int idProc, cantProc;

    MPI_Init(&argc, &argv);                   // Inicializacion del entorno MPI
    //MPI_Comm_size(MPI_COMM_WORLD, &cantProc); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);   // Obtenemos la identificacion de nuestro proceso en el comunicador global

    if (idProc % 2 == 0)
    {
        //#procesos pares
        cout
            << "soy el proceso: " << idProc << " un proceso par" << endl;
    }
    else
    {
        //#procesos impares
        cout << "soy el proceso: " << idProc << " un proceso impar" << endl;
    }

    MPI_Finalize();

    return 0;
}
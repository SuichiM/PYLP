#include "mpi.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    int idProc, cantProc, lng, sumaParcial, sumaGlobal;

    MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos

    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);   // Obtenemos el valor de nuestro identificador
    MPI_Comm_size(MPI_COMM_WORLD, &cantProc); // Obtenemos el numero de procesos en el comunicador global

    lng = cantProc * 5;
    sumaParcial = 0;
    int vectorGlobal[lng];
    int vectorLocal[5];

    //cargo el vector
    if (idProc == 0)
    {
        for (int i = 0; i < lng; i++)
        {
            vectorGlobal[i] = rand() % 100;
        }

        // imprimir el vector generado
        cout << "Vector Global: " << endl;
        for (int i = 0; i < lng; i++)
        {
            cout << vectorGlobal[i] << " - ";
        }
        cout << endl;
    }

    //distribuir el vector con mpi scatter
    MPI_Scatter(
        &vectorGlobal[0],
        5,
        MPI_INT,
        &vectorLocal[0],
        5,
        MPI_INT,
        0,
        MPI_COMM_WORLD);

    //imprimo cada vector local
    cout
        << "Vector recibido en el proceso: " << idProc << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << vectorLocal[i] << " - ";
    }
    cout << endl;

    //OPERO EN CADA PROCESO
    //multiplicar cada vector local por el id del proceso
    for (int i = 0; i < 5; i++)
    {
        vectorLocal[i] = vectorLocal[i] % (idProc + 2) == 0 ? 1 : 0;
    }

    //unir los vectores local en el proceso 0 con MPI_Gather
    MPI_Gather(
        &vectorLocal[0],
        5,
        MPI_INT,
        &vectorGlobal[0],
        5,
        MPI_INT,
        0,
        MPI_COMM_WORLD);

    MPI_Reduce(&sumaParcial,
               &sumaGlobal,
               1,
               MPI_INT,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    if (idProc == 0)
    {
        cout << "Vector Final: " << endl;
        for (int i = 0; i < lng; i++)
        {
            cout << vectorGlobal[i] << " - ";
        }
        cout << endl;
    }

    MPI_Finalize();

    return 0;
}
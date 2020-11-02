#include "mpi.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    int idProc, cantProc;

    MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos

    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);   // Obtenemos el valor de nuestro identificador
    MPI_Comm_size(MPI_COMM_WORLD, &cantProc); // Obtenemos el numero de procesos en el comunicador global

    int lng = cantProc * 5;
    int vectorGlobal[lng];
    int multiplos = 0;
    int mod = 0;
    int max;

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
    MPI_Bcast(
        &vectorGlobal[0],
        lng,
        MPI_INT,
        0,
        MPI_COMM_WORLD);

    //imprimo cada vector recibido
    cout
        << "Vector recibido en el proceso: " << idProc << endl;

    for (int i = 0; i < lng; i++)
    {
        cout << vectorGlobal[i] << " - ";
    }
    cout << endl;

    //calculo los multiplos de los primeros "catnProc" elementos
    for (int i = 0; i < cantProc; i++)
    {
        if (idProc == i)
        {
            mod = vectorGlobal[i];
            for (int j = 0; j < lng; j++)
            {
                if (vectorGlobal[j] % mod == 0)
                {
                    ++multiplos;
                }
            }
            //imprimo los multiplos obtenidos por el proceso
            cout
                << "El elemento " << vectorGlobal[i] << " tuvo: " << multiplos << " multiplos ";
            cout << endl;
        }
    }

    //obtengo el que mas multiplos tuvo
    MPI_Reduce(&multiplos,
               &max,
               1,
               MPI_INT,
               MPI_MAX,
               0,
               MPI_COMM_WORLD);

    if (idProc == 0)
    {
        cout
            << "El numero maximo de multiplos obtenido fue: " << max << endl;
    }

    MPI_Finalize();

    return 0;
}
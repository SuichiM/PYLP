#include "mpi.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    int idProc, buzon, cantProc;

    MPI_Status estado;

    MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos

    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);   // Obtenemos el valor de nuestro identificador
    MPI_Comm_size(MPI_COMM_WORLD, &cantProc); // Obtenemos el numero de procesos en el comunicador global

    //Envia y recibe mensajes
    if (idProc == 0)
    {
        MPI_Send(
            &idProc,
            1,          // tamaño del mensaje, en este caso es un entero asi que es uno. Si es un array sera el tamaño del array
            MPI_INT,    // Tipo de dato que envias
            idProc + 1, // pid del proceso destino
            0,          //etiqueta
            MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&buzon // Referencia al vector donde se almacenara lo recibido
                 ,
                 1 // tamaño del vector a recibir
                 ,
                 MPI_INT // Tipo de dato que recibe
                 ,
                 idProc - 1 // pid del proceso origen de la que se recibe
                 ,
                 MPI_ANY_TAG // tiqueta de tipo entero o MPI_ANY_TAG para recibir cualquier etiqueta
                 ,
                 MPI_COMM_WORLD // Comunicador por el que se recibe
                 ,
                 &estado); // estructura informativa del estado

        cout << "Soy el proceso " << idProc << " y he recibido " << buzon << endl;

        if (idProc < cantProc - 1)
        {
            MPI_Send(
                &idProc,
                1,          // tamaño del mensaje, en este caso es un entero asi que es uno. Si es un array sera el tamaño del array
                MPI_INT,    // Tipo de dato que envias
                idProc + 1, // pid del proceso destino
                0,          // etiqueta de tipo entero
                MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}
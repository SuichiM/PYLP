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

    int x = 5;
    lng = cantProc * x;
    sumaParcial = 0;
    sumaGlobal = 0;
    int v1[lng];
    int v2[lng];
    int vectorLocal1[x];
    int vectorLocal2[x];

    //cargo el vector
    if (idProc == 0)
    {
        for (int i = 0; i < lng; i++)
        {
            v1[i] = i;
            v2[i] = i * 2;
        }

        // imprimir el vector1 generado
        cout << "Vector 1: " << endl;
        for (int i = 0; i < lng; i++)
        {
            cout << v1[i] << " - ";
        }
        cout << endl;

        // imprimir el vector2 generado
        cout << "Vector 2: " << endl;
        for (int i = 0; i < lng; i++)
        {
            cout << v2[i] << " - ";
        }
        cout << endl;
    }

    //distribuir el vector1 con mpi scatter
    MPI_Scatter(
        &v1[0],           //Dirección inicial del buffer de salida
        x,                //Número de elementos que se envía a cada proceso del comunicador
        MPI_INT,          //Tipo de dato que se va a enviar
        &vectorLocal1[0], //Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
        x,                //Número de elementos que espera recibir cada proceso
        MPI_INT,          //Tipo de datos de los elementos a recibir
        0,                //Rango del proceso que hace el envio
        MPI_COMM_WORLD    //Comunicador por el que realizar la comunicación.
    );

    //distribuir el vector2 con mpi scatter
    MPI_Scatter(
        &v2[0],           //Dirección inicial del buffer de salida
        x,                //Número de elementos que se envía a cada proceso del comunicador
        MPI_INT,          //Tipo de dato que se va a enviar
        &vectorLocal2[0], //Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
        x,                //Número de elementos que espera recibir cada proceso
        MPI_INT,          //Tipo de datos de los elementos a recibir
        0,                //Rango del proceso que hace el envio
        MPI_COMM_WORLD    //Comunicador por el que realizar la comunicación.
    );

    //OPERO CON LOS VECTORES LOCALES
    //imprimo cada vector local
    //vlocal1
    cout
        << "Vector recibido en el proceso: " << idProc << endl;

    for (int i = 0; i < x; i++)
    {
        cout << vectorLocal1[i] << " - ";
    }
    cout << endl;

    //vlocal2
    cout
        << "Vector recibido en el proceso: " << idProc << endl;

    for (int i = 0; i < x; i++)
    {
        cout << vectorLocal2[i] << " - ";
    }
    cout << endl;

    //multiplicar cada vector local
    for (int i = 0; i < x; i++)
    {
        sumaParcial += vectorLocal1[i] * vectorLocal2[i];
    }

    MPI_Reduce(&sumaParcial,
               &sumaGlobal,
               1,
               MPI_INT,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    if (idProc == 0)
    {
        cout << "El resultado de la operacion es: " << sumaGlobal << endl;

        cout << endl;
    }

    MPI_Finalize();

    return 0;
}
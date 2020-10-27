// Realiza el producto escalar entre dos vectores, distribuidos 
// de igual manera a cada proceso. Funciones utilizadas: MPI_Scatter y MPI_Reduce.

#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

int main (int argc, char *argv[])
{
    int sizeVec, size, rank;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Creación y carga de vectores
    sizeVec = size * 5; // número 5 propuesto en la consigna por la cátedra.
    vector<int> vectorA, vectorB, vecLocalA, vecLocalB;
    vectorA.resize(sizeVec, 0); // resize modifica el tamaño del vector al valor especificado.
    vectorB.resize(sizeVec, 0);
    vecLocalA.resize(sizeVec/size, 0);
    vecLocalB.resize(sizeVec/size, 0);
    if (rank == 0) {
        for (int i = 0; i < sizeVec; ++i) {
            vectorA[i] = i + 1; // vectorA 1, 2, 3, ..., sizeVec
            vectorB[i] = (i + 1)*2; // vectorB 2, 4, 6, ..., sizeVec*2
            }
    }
    // Distribución de los valores del vector A
    MPI_Scatter(&vectorA[0], // Valores a compartir
            sizeVec / size, // Cantidad de datos a enviar a cada proceso
            MPI_INT, // Tipo de dato que se enviará
            &vecLocalA[0], // Variable donde se recibe los datos
            sizeVec / size, // Cantidad de datos que se recibe en cada proceso
            MPI_INT, // Tipo de dato que se recibirá
            0,  // Proceso principal que reparte los datos
            MPI_COMM_WORLD); // Comunicador global

    // Distribución de los valores del vector B
    MPI_Scatter(&vectorB[0], 
            sizeVec / size, 
            MPI_INT, 
            &vecLocalB[0], 
            sizeVec / size, 
            MPI_INT, 
            0,  
            MPI_COMM_WORLD);

    // Producto escalar entre los vectores.
    int producto = 0;
    int prod = 0;
    cout << " Soy el proceso " << rank << endl;
    for (int i = 0; i < sizeVec / size; ++i) {
        prod = vecLocalA[i] * vecLocalB[i];
        cout << " Producto escalar: " << vecLocalA[i]<<" * "<< vecLocalB[i]<<" = "<< prod << endl;
        producto += prod;
    }
    cout << "La sumatoria es " << producto  << endl;
    int total;

    // Se reúnen los datos en un solo proceso por medio de la operación suma.
    MPI_Reduce(&producto, // Elemento a enviar
            &total, // Variable donde se almacena los datos
            1, // Cantidad de datos a reunir
            MPI_INT, // Tipo del dato que se reunirá
            MPI_SUM, // Operacion aritmetica a aplicar
            0, // Proceso que recibira los datos
            MPI_COMM_WORLD); // Comunicador
 
    if (rank == 0)
        cout << " Sumatoria total de los procesos: " << total << endl;

    MPI_Finalize();
    return 0;
}
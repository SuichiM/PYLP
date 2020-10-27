#include "mpi.h"
#include <iostream>
using namespace std;
 
#define ROOT 0
#define SLICE 5

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv); // inicio del entorno MPI
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ID de proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // cantidad de procesos en el comunicador global

    int vectorSize = size * SLICE;
    int vector[vectorSize], result[vectorSize];
    int mailbox[SLICE]; // buzon para recibir los elementos

    if (rank == ROOT) {
        // CARGAR VECTORES DE FORMA ALEATORIA
        for (int i = 0; i < vectorSize; i++) {
            vector[i] = rand() % 100;
        }

        // IMPRIMIR VECTOR
        cout << endl;
        cout << "VECTOR: " << endl;
        for (int i = 0; i < vectorSize; i++) {
            cout << vector[i] << " - ";
        }
        cout << endl;
    }

    MPI_Scatter(
        &vector,       // lo que se va a distribuir entre los procesos
        SLICE,          // numero de elementos que se envia a cada proceso
        MPI_INT,        // tipo de dato de lo que se va a enviar
        &mailbox,      // en donde cada proceso hace la recepcion
        SLICE,          // numero de elementos a recibir
        MPI_INT,        // tipo de dato de lo que se va a recibir
        ROOT,           // quien realiza el envio
        MPI_COMM_WORLD  // los procesos quienes particiban en la distribuicion
    );

    cout << endl;
    cout << "MAIL BOX  de " << rank << endl;
    for (int i = 0; i < SLICE; i++) {
        cout << mailbox[i] << " - ";
    }
    cout << endl;
    
    int partialResults[SLICE];
    for (int i = 0; i < SLICE; i++) {
        partialResults[i] = mailbox[i] % (rank + 2) == 0 ? 1 : 0;
    }
    cout << endl;

    MPI_Gather(
        &partialResults, // lo que se va emitir
        SLICE, // cantidad de elementos a emitir
        MPI_INT, // tipo de dato de lo que se va a emitir
        &result, // en donde se recibe los elementos
        SLICE, // cantidad de elementos a recibir
        MPI_INT, // tipo de dato de lo que se va a recibir
        ROOT, // quien lo va a recibir
        MPI_COMM_WORLD // entre quienes se hace la reduccion
    );

    if (rank == ROOT) {
        cout << endl;
        cout << endl;
        cout << endl;
        // IMPRIMIR VECTOR
        cout << "RESULTADO: " << endl;
        for (int i = 0; i < vectorSize; i++) {
            cout << result[i] << " - ";
        }
        cout << endl;
        cout << endl;
    }

 
    MPI_Finalize();
    
    return 0;
}
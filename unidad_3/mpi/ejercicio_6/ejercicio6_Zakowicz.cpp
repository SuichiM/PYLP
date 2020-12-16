// Crear un algoritmo donde el proceso 0 cree y envíe un vector *Global* mediante `MPI_Bcast`.
// Cada proceso debe ir contabilizando todos los elementos del vector, que sean 
// multiplo del elemento en la posicion `rango` del proceso.

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

  // Creación y carga del vector global
    sizeVec = size * 5; // número 5 propuesto en la consigna por la cátedra.
    vector<int> vectorGlobal; 
    vectorGlobal.resize(sizeVec, 0); // resize modifica el tamaño del vector al valor especificado.
    if (rank == 0) {
        cout << " Vector global " << endl;
        for (int i = 0; i < sizeVec; ++i) {
            vectorGlobal[i] = (i + 1) * 2; // vectorGlobal 2, 4, 6, ..., sizeVec  
            cout << vectorGlobal[i] << " - ";         
            } 
        cout << endl; 
    }
    // Envía un mensaje desde el proceso 0 a todos los procesos del mismo grupo.
    MPI_Bcast(&vectorGlobal[0],
              sizeVec, 
              MPI_INT,
			  0, 
              MPI_COMM_WORLD);

    // Impresion del vector global recibido en cada proceso.
    cout << " Vector recibido en el proceso " << rank << endl;
    for (int i = 0; i < sizeVec; i++){
        cout << vectorGlobal[i] << " - ";
    }
    cout << endl;
    
    // Calcúla si el valor en la posición rank es múltiplo 
    // de los demás elementos del vector.
    int multiplos = 0;
    for (int i = 0; i < sizeVec; i++) {
      if (vectorGlobal[i] % vectorGlobal[rank] == 0){
           multiplos += 1;
        }
    } 
    // Impresion de la cantidad de múltiplos del elemento en la posición rank.
    cout << " Múltiplos del elemento " <<vectorGlobal[rank]<< " situado en la posición " <<rank<< ":" <<multiplos<<endl;
    
    int maxTotal = 0;

   // Operación de reducción global sobre cada uno de los miembros del grupo.
   // Obtiene la máxima cantidad de múltiplos arrojádo por cada proceso.
    MPI_Reduce(
        &multiplos,
        &maxTotal,
        1,
        MPI_INT,
        MPI_MAX,
        0,
        MPI_COMM_WORLD);

    // Se imprime el máximo número de múltiplos pertenecientes a cada proceso.
    if (rank == 0){
     cout << "El proceso " <<rank<< " obtuvo la mayor cantidad de múltiplos "<<maxTotal<< endl;
      
    }

    MPI_Finalize();
    return 0;
}
#include "mpi.h"
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#define NVecLoc 5

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
    
    vector<int>  VecGeneral, VecLocal;
    VecLocal.resize(NVecLoc, 0);
    VecGeneral.resize(5*size, 0);

    if(rank==0){ //Proceso Raiz
        //rellenamos vectores con numero pseudoaleatorios
        for (long i = 0; i < VecGeneral.size(); i++){
            VecGeneral[i] = rand() % 100;            
        }
        //Imprimimos el vector con los numeros aleatorios
        cout << "Vector Inicial: ";
        cout<< "[";
        for (int i = 0; i < VecGeneral.size()-1; i++){
            cout<< VecGeneral[i] << ", ";
        }
        cout << VecGeneral[VecGeneral.size()-1] << "]" << endl;
    }
    //desde el Vec completo, se dividen los elementos en n/size  y se mandan a cada VecLocal de cada proceso que no es el raiz
    MPI_Scatter(&VecGeneral[0], NVecLoc, MPI_INT, &VecLocal[0], NVecLoc, MPI_INT, 0, MPI_COMM_WORLD);

    //Cada proceso realiza lo de la consigna con su fraccion del vector.
    for (int i = 0; i < VecLocal.size(); i++){
        VecLocal[i] = (VecLocal[i] % (rank + 2) == 0) ? 1 : 0;
    }
    
    //Se centraliza  todo en un unico vector en el proceso raiz.
    MPI_Gather(&VecLocal[0], NVecLoc, MPI_INT, &VecGeneral[0], NVecLoc, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0){ //Aca se imprime el vector general
        cout << "Vector Resultante: ";
        cout<< "[";
        for (int i = 0; i < VecGeneral.size()-1; i++){
            cout<< VecGeneral[i] << ", ";
        }
        cout << VecGeneral[VecGeneral.size()-1] << "]" << endl;
    }
    MPI_Finalize();
    return 0;

}
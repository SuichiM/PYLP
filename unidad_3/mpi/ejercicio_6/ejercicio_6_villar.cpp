#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;
#define N 5
int main(int argc, char *argv[])
{
    int rank, size, cantMult, multMax;
    multMax = 0;
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
    
    vector<int>  VecGeneral;
    VecGeneral.resize(size*N, 0);

    if(rank==0){ //Proceso Raiz
        //rellenamos vectores con numero pseudoaleatorios
        for (int i = 0; i < VecGeneral.size(); i++){
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

    MPI_Bcast(&VecGeneral[0], size*N, MPI_INT, 0, MPI_COMM_WORLD);
    cantMult = 0;
    for (int i = 0; i < VecGeneral.size(); i++){
        cantMult += (VecGeneral[i] % VecGeneral[rank]==0) ? 1 : 0;
    }


    cout<< "El proceso "<<rank << " verifica que el numero en su posicion (" << VecGeneral[rank]<<") tiene "<< cantMult << " multiplos"<< endl;

    MPI_Reduce(&cantMult, &multMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if(rank == 0)
        cout<<"La mayor cantidad de multiplos que tuvo un proceso fue: " << multMax <<endl;
    MPI_Finalize();
    return 0;
}
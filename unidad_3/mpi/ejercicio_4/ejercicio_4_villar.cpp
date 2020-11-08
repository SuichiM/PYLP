#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, n;
    
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
    
    n=size* 5;
    vector<long>  VecA, VecB, VecALocal, VecBLocal;
    VecA.resize(n, 0);
    VecB.resize(n, 0);
    VecALocal.resize(n/size, 0);
    VecBLocal.resize(n/size, 0);

    if(rank==0){ //Proceso Raiz
        //rellenamos vectores
        for (long i = 0; i < n; i++)
        {
            VecA[i] = i+1;
            VecB[i] = (i+1);
        }    
    }
    //desde el Vec completo, se dividen los elementos en n/size  y se mandan a cada VecLocal de cada proceso que no es el raiz
    MPI_Scatter(&VecA[0], n/size, MPI_LONG, &VecALocal[0], n/size, MPI_LONG, 0, MPI_COMM_WORLD);
    MPI_Scatter(&VecB[0], n/size, MPI_LONG, &VecBLocal[0], n/size, MPI_LONG, 0, MPI_COMM_WORLD); 
    
    //A partir de aca cada proceso calcula el escalar de cada pedazo dde vector que le toco en VecLocal.
    long total_local = 0;
    for (long i = 0; i < n/size; i++){
        total_local += VecALocal[i] * VecBLocal[i];
    }
    long total; //Aca se centraliza los totales de cada proceso con MPI_Reduce
    
    //cada total local, se suma en el total, que se manda al raiz nuevamente.
    MPI_Reduce(&total_local, &total, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        cout << "El total es: "<< total << endl;
    }  
    
    MPI_Finalize();
    
    return 0;
}
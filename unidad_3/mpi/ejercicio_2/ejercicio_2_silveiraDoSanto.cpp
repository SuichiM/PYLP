#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size;
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
 
    if (rank % 2 == 0){
        cout<<"¡Hola Mundo desde el proceso par "<<rank<<" de "<<size<<" que somos!"<<endl;
    }else{
        cout<<"¡Hola Mundo desde el proceso impar "<<rank<<" de "<<size<<" que somos!"<<endl;
    }
        
 
    
    MPI_Finalize();
    
    return 0;
}
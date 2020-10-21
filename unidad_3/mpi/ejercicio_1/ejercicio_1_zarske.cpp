#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size;
 
    MPI_Init(&argc, &argv);  //se inicia la comunicación paralela entre procesos

    MPI_Comm_size(MPI_COMM_WORLD, &size); //se obtiene en "size" el rango del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //se obtiene en "rank" el tamaño del comunicador MPI_COMM_WORLD
 
    printf("¡Hola Mundo desde el proceso %d de %d que somos!\n", rank, size);
 
    MPI_Finalize();//se finaliza la comunicación paralela entre procesos
    
    return 0;
}
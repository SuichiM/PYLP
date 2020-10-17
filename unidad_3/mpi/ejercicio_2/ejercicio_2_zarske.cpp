#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size;
 
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank % 2 == 0){

        printf("Soy el proceso:  %d, y soy un proceso Par \n", rank);

    }else{

        printf("Soy el proceso:  %d, y soy un proceso Impar \n", rank);

    }
 
    MPI_Finalize();
    
    return 0;
}
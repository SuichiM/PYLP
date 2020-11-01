#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
    int rank, size;

    MPI_Init(&argc, &argv); //Iniciamos MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Guardamos en size la cantidad de procesos que se vayan ejecutando
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Guardamos en rank el id del proceso actual ejecutandose

    cout<<"¡Hola Mundo desde el proceso "<<rank<<" de "<<size<<" que somos!"<<endl;
    MPI_Finalize();
    
    return 0;
}
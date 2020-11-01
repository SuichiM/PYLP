
#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, buzon, size;
    MPI_Status estado;
 
    MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador
    MPI_Comm_size (MPI_COMM_WORLD, &size); // Obtenemos el tamanio del comunicador global
 
    //Envia y recibe mensajes
    if(rank == 0){
        MPI_Send(
        &rank ,
        1, 
        MPI_INT, // Tipo de dato que envias
        rank+1, // pid del proceso destino
        0, //etiqueta
        MPI_COMM_WORLD
      ); 
    }else{
      cout << rank << " - antes de recibir:" << buzon << endl;

      MPI_Recv(&buzon // Referencia al vector donde se almacenara lo recibido
        ,1 // tamaño del vector a recibir
        ,MPI_INT // Tipo de dato que recibe
        ,rank-1 // pid del proceso origen de la que se recibe
        ,0 // etiqueta
        ,MPI_COMM_WORLD // Comunicador por el que se recibe
        ,&estado); // estructura informativa del estado

      cout<< "Soy el proceso "<<rank<<" y he recibido "<<buzon<<endl;

      if (rank < size-1) { // si el id del proceso es menor que cantidad de procesos - 1 del comunicador
        MPI_Send(
          &rank ,
          1, 
          MPI_INT, // Tipo de dato que envias
          rank+1, // pid del proceso destino
          0, //etiqueta
          MPI_COMM_WORLD
        );
      }

 
    }
 
	
    MPI_Finalize();
    

    return 0;
}
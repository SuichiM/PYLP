#include "mpi.h"
#include <iostream>
using namespace std;

/*
Crear un algoritmo que realice el producto escalar de dos vectores 
donde el tamaño de los vectores es de NP (cantidad de procesos lanzados) por 5.

Para realizar el producto escalar, lo que vamos a tener que hacer, es enviar a cada proceso una porcion de los vectores originales 
con `MPI_Scatter` *(video 1)*.
Cada proceso ira haciendo el producto de los elementos de los vectores que recibió almacenadolos en una variable `producto`. 
Luego todos los productos locales se reducirán en el proceso 0 con `MPI_Reduce`.
*/

int main(int argc, char *argv[])
{
    //inicializamos las variable a utilizar
    int rank, size, total, elementos;

    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    //cantidad de elementos por proceso que usaremos
    elementos = 5;
    //calculamos la cantidad total que tendra nuestro arreglo principal
    total = size * elementos;

    //defino los vectores principales
    float vector1[total], vector2[total];
    //defino los vectores locales donde cada proceso recibira los valores enviados por MPI_Scatter
    float vector1_local[elementos], vector2_local[elementos];

    //defino variables para realizar las operaciones requeridas
    float suma_parcial;                      // lo usara cada proceso en la suma local del mismo
    float sumas_parciales[size], suma_total; // El proceso raiz obtendra los valores de todos los procesos

    //inicializo las variables de sumas
    suma_total = 0;   //variable que usara el proceso 0 (raiz)
    suma_parcial = 0; //variable que usaran en todos los procesos para sumar

    //Si soy el proceso 0 (raiz) cargo los vectores principales
    if (rank == 0)
    {
        for (int i = 0; i < total; i++)
        {
            vector1[i] = i + 3;
            vector2[i] = i + 2;
        }
    }

    //divido y envio el vector 1 a los otros procesos siendo padre el resto de procesos recibe los datos con esta funciones
    MPI_Scatter(vector1, elementos, MPI_FLOAT, vector1_local, elementos, MPI_FLOAT, 0, MPI_COMM_WORLD);

    //divido y envio el vector 2 a los otros procesos siendo padre el resto de procesos recibe los datos con esta funciones
    MPI_Scatter(vector2, elementos, MPI_FLOAT, vector2_local, elementos, MPI_FLOAT, 0, MPI_COMM_WORLD);

    //cada proceso realiza el calculo de una parte del vector principal
    for (int i = 0; i < elementos; i++)
    {
        suma_parcial = suma_parcial + (vector1_local[i] * vector2_local[i]);
        cout << "Proceso: " << rank
             << " vector1: " << vector1_local[i]
             << " vector2: " << vector2_local[i]
             << " resultado parcial: " << suma_parcial << endl;
    }

    //Vada proceso envia las variables y el proceso raiz recibe las variables de todos los procesos
    MPI_Reduce(&suma_parcial, &suma_total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    //si soy el proceso raiz, hago la suma de las variables que recibi
    if (rank == 0)
    {
        cout << "Suma Total: " << suma_total << endl;
    }

    //una vez que cada proceso tiene su valor lo envia al proceso raiz

    // Terminamos la ejecucion de los procesos, despues de esto solo existira
    // la hebra 0
    // ¡Ojo! Esto no significa que los demas procesos no ejecuten el resto
    // de codigo despues de "Finalize", es conveniente asegurarnos con una
    // condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();

    return 0;
}
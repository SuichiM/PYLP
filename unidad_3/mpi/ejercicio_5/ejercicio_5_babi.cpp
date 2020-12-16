#include "mpi.h"
#include <iostream>
using namespace std;

/*
Crear un algoritmo que distribuya un vector *"Global"* de tamaño NP(cantidad de procesos lanzados) \* 5 entre los procesos lanzados `MPI_Scatter`. 
Cada proceso va a recibir los valores en un vector *"Local"* de tamaño 5. 
Cada proceso debe recorrer el vector y modificarlo escribiendo en cada posición:
    un 1 si el elemento de esa posición es multiplo del rango del proceso + 2  
    un 0 si no lo es.
Luego todos los vectores *"Locales"* se unificarán en el proceso 0 `MPI_Gather`.
*/

int main(int argc, char *argv[])
{
    //inicializamos las variable a utilizar
    int rank, rank_multiplo, size, total, elementos;

    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    //cantidad de elementos por proceso que usaremos
    elementos = 5;
    //calculamos la cantidad total que tendra nuestro arreglo principal
    total = size * elementos;
    //necesitamos que sean multiplo del rank + 2
    rank_multiplo = rank + 2;

    //defino los vectores principales
    int vector1[total];
    //defino los vectores locales donde cada proceso recibira los valores enviados por MPI_Scatter
    int vector1_local[elementos];

    //defino variables para realizar las operaciones requeridas
    int vectores_locales[total];

    //Si soy el proceso 0 (raiz) cargo los vectores principales
    if (rank == 0)
    {
        for (int i = 0; i < total; i++)
        {
            vector1[i] = (i + 4) * 2;
        }
    }

    //divido y envio el vector 1 a los otros procesos siendo padre el resto de procesos recibe los datos con esta funciones
    MPI_Scatter(vector1, elementos, MPI_INT, vector1_local, elementos, MPI_INT, 0, MPI_COMM_WORLD);

    //cada proceso realiza el calculo de una parte del vector principal
    for (int i = 0; i < elementos; i++)
    {
        if (vector1_local[i] % rank_multiplo == 0)
        {
            cout << vector1_local[i] << " es Multiplo de " << rank_multiplo << endl;
            vector1_local[i] = 1;
        }
        else
        {
            vector1_local[i] = 0;
        }
    }

    //Cada proceso envia las variables y el proceso raiz recibe las variables de todos los procesos
    MPI_Gather(vector1_local, elementos, MPI_INT, vectores_locales, elementos, MPI_INT, 0, MPI_COMM_WORLD);

    //si soy el proceso raiz, muestro los multiplos que encontre dependiendo del proceso que los ejecuto
    if (rank == 0)
    {
        cout << "Arreglo con los valores devueltos: Posicion - Numero - 1 / 0 Si es multiplo o no. " << endl;
        for (int i = 0; i < total; i++)
        {
            cout << "Posicion: " << i << " - valor: " << vector1[i] << " - Multiplo? " << vectores_locales[i] << endl;
        }
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
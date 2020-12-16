#include "mpi.h"
#include <iostream>
using namespace std;

/*
Crear un algoritmo donde el proceso 0 cree y envíe un vector *"Global"* 
de tamaño NP(cantidad de procesos lanzados) \* 5 a todos procesos mediante `MPI_Bcast`. 

Cada proceso va a recibir dicho valores, utilizando la misma variable de origen.

Cada proceso debe ir contabilizando todos los elementos del vector, que sean multiplo del 
elemento en la posicion `rango` del proceso.

> el proceso 0 debe verificar cuantos elementos son multiplos del elemento en la posicion 0
> el proceso 1 debe verificar cuantos elementos son multiplos del elemento en la posicion 1
> el proceso 2 debe verificar cuantos elementos son multiplos del elemento en la posicion 2
> el proceso n debe verificar cuantos elementos son multiplos del elemento en la posicion n

Luego imprimir el resultado por pantalla y opcionalmente obtener cual es el que mayor multiplos tuvo mediante la instruccion `MPI_Reduce` .
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

    //defino los vectores principales
    int vector1[total];

    //defino variables para realizar las operaciones requeridas
    int vector_multiplos[total];
    int maximo_local = 0;
    int valor_maximo = 0;

    //Si soy el proceso 0 (raiz) cargo los vectores principales
    if (rank == 0)
    {
        for (int i = 0; i < total; i++)
        {
            vector1[i] = i + 2;
        }
    }

    //divido y envio el vector 1 a los otros procesos siendo padre el resto de procesos recibe los datos con esta funciones
    MPI_Bcast(vector1, total, MPI_INT, 0, MPI_COMM_WORLD);

    //cada proceso realiza el calculo de una parte del vector principal
    for (int i = 0; i < total; i++)
    {
        if (vector1[i] % vector1[rank] == 0)
        {
            cout << "Soy el proceso " << rank << " y el valor " << vector1[i] << " es Multiplo de " << vector1[rank] << endl;
            if (vector1[i] > maximo_local)
            {
                maximo_local = vector1[i];
            }
        }
    }

    //se reducen todo el proceso y el raiz recibe las variables de todos los procesos
    MPI_Reduce(&maximo_local, &valor_maximo, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    //si soy el proceso raiz, muestro los multiplos que encontre dependiendo del proceso que los ejecuto
    if (rank == 0)
    {
        cout << "El valor máximo es: " << valor_maximo << endl;
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
#include <omp.h>
#include <iostream>

#define N 10
#define nthreads 4

int main()
{
    int thread;
    omp_set_num_threads(nthreads);
    printf("Static \n");
#pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
#pragma omp for schedule(static)
        for (int i = 0; i < N; i++)
        {
            printf("Soy %d ejecuto la iteracion %d \n", thread, i);
            //std::cout << "Soy el proceso " << thread << " ejecuto al iteracion " << i << std::endl;
        }
    }
    printf("Dynamic \n");
#pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
#pragma omp for schedule(dynamic)
        for (int i = 0; i < N; i++)
        {
            printf("Soy %d ejecuto la iteracion %d \n", thread, i);
            //std::cout << "Soy el proceso " << thread << " ejecuto al iteracion " << i << std::endl;
        }
    }
    printf("Guided \n");
#pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
#pragma omp for schedule(guided)
        for (int i = 0; i < N; i++)
        {
            printf("Soy %d ejecuto la iteracion %d \n", thread, i);
            //std::cout << "Soy el proceso " << thread << " ejecuto al iteracion " << i << std::endl;
        }
    }
    printf("Auto \n");
#pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
#pragma omp for schedule(auto)
        for (int i = 0; i < N; i++)
        {
            printf("Soy %d ejecuto la iteracion %d \n", thread, i);
            //std::cout << "Soy el proceso " << thread << " ejecuto al iteracion " << i << std::endl;
        }
    }
}

//Punto 2: Al agregar #pragma omp for antes de una sentencia for el programa controla la ejecucion de for entre todos los procesos
//esto quiere decir que entre todos realizan 1 vez el for osea, solo imprime una vez del 0 al 9 que de caso contrario
//cada hilo haria un for imprimiendo del 0 al 9

/*Punto 3.1 schedule static: Define una cantidad del bucle a cada proceso, se puede definir agregando un parametro mas al schedule(static, CANTIDAD_A_DIVIDIR)
Ejemplo si usamos (static,1) dara una iteracion al proceso 0 luego al 1, 2 y 3. y empezara a repartir nuevamente desde el 0 una iteracion por proceso
*/
/*Punto 3.2 schedule dynamic: Define de manera dinamica y variante quien resuelve cada paso del for
Puede suceder que algunos procesos reciban mucho mas trabajo que otros.
*/
/*Punto 3.4 schedule auto: Selecciona automaticamente la forma mas eficiente de distribucion 
*/
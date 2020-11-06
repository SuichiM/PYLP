#include <omp.h>
#include <iostream>

#define N 10
#define nthreads 4

int main (){
    int thread;
    omp_set_num_threads(nthreads);
    #pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();

    	// 2-> Indicamos que vamos a entrar a un bucle for, ya no se ejecuta el for por cada proceso, sino que se distribuyen las iteraciones del for entre los 4 procesos que lanzamos (algunos procesos ejecutan 3 iteraciones, otros 2, etc)
        #pragma omp for schedule(dynamic, 2) // 3-> Configuramos el planificador en "dynamic", haciendo que el mismo asigne en tiempo de ejecución de a 2 iteraciones al hilo que este en memoria 
        for (int i = 0 ; i < N; i++)
        {
            printf("Soy el proceso %d ejecuto la iteracion %d \n",thread,i);
        }

    }
}
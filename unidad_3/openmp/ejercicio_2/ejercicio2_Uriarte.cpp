#include <omp.h>
#include <iostream>

//definimos la cantidad de iteraciones y de procesos
#define X 5
#define nthreads 4

int main()
{
    int thread;
    omp_set_num_threads(nthreads);
#pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();

//El segundo parametro del schedule define los siguiente
// Chunk Sizes
//We can split the difference between static and dynamic scheduling by using chunks in a dynamic schedule.Here,
//each thread will take a set number of iterations, called a “chunk”,
//execute it, and then be assigned a new chunk when it is done.

// Se define de forma estatica antes de la ejecucion
// #pragma omp for schedule(static, 2)
// for (int i = 0 ; i < X; i++){
//   #pragma omp critical
//   std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
// }

//Se crea una cola de la cual los procesos van recogiendo el siguiente bloque disponible
// #pragma omp for schedule(dynamic, 2)
// for (int i = 0 ; i < X; i++){
//   #pragma omp critical
//   std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
// }

//This scheduling policy is similar to a dynamic schedule, except that the chunk size changes as the program runs. 
//It begins with big chunks, but then adjusts to smaller chunk sizes if the workload is imbalanced.
// #pragma omp for schedule(guided, 2)
// for (int i = 0 ; i < X; i++){
//   #pragma omp critical
//   std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
// }

// Manejado por el sistema operativo
#pragma omp for schedule(auto)
        for (int i = 0; i < X; i++)
        {
#pragma omp critical
            std::cout << "Soy el proceso " << thread << " ejecuto al iteracion " << i << std::endl;
        }
    }
    return 0;
}
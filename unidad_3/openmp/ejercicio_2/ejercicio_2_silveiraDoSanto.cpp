#include <omp.h>
#include <iostream>

#define N 20
#define nthreads 4

int main (){

  int thread;

  omp_set_num_threads(nthreads);

  #pragma omp parallel private(thread)
  {
      thread = omp_get_thread_num();
      #pragma omp for schedule(dynamic, 2) // el static divide la cantidad de datos segun el argumento pasado ordenado por los hilos
      //#pragma omp for schedule(static, 2)
      //#pragma omp for schedule(guided, 2)
      //#pragma omp for schedule(auto)                                    // el dynamic divide los datos de forma aleatoria para cada hilo
      for (int i = 0 ; i < N; i++){
        #pragma omp critical
          std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }

  }
}
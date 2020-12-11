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


      // Divide el bucle en porciones de igual tamano o tanto como sea posible en caso de no ser posible.
      // #pragma omp for schedule(static, 2)
      // for (int i = 0 ; i < N; i++){
      //   #pragma omp critical
      //   std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      // }

      // Arma un cola de bloques de bucles de iteracion de tamanio de porcion para cada hilo. Cuando un hilo
      // termina, recupera el siguiente bloque de la cola
      // #pragma omp for schedule(dynamic, 2)
      // for (int i = 0 ; i < N; i++){
      //   #pragma omp critical
      //   std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      // }

      // Similar al dinamico, pero el tamanio de porcion comienza grande y va decrementando.
      // #pragma omp for schedule(guided, 2)
      // for (int i = 0 ; i < N; i++){
      //   #pragma omp critical
      //   std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      // }

      // lo maneja el SO la planificacion del bucle
      #pragma omp for schedule(auto)
      for (int i = 0 ; i < N; i++){
        #pragma omp critical
        std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }

  }
  return 0;
}
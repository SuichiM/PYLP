#include <omp.h>
#include <iostream>
 
int main (){
 
int nthreads;
int thread;
int nueva_variable = 777;

omp_set_num_threads(10); // establece la cantidad de hilos que se ejecutaran

#pragma omp parallel private(nthreads, thread) firstprivate(nueva_variable)
  {
  // al eliminar la clausula "private" las variables globales seran compartidas por todos los hilos

  // con "private" las variables son independientes a cada hilo; pero pierden el valor declarad anteriormente; para mantenerlo se usa "firstprivate"
  thread = omp_get_thread_num();
 
  nthreads = omp_get_num_threads();
    
  #pragma omp critical
    printf("Hola Mundo soy la hebra = %d de %d que somos. Esta es la variable nueva =  %d \n", thread, nthreads, nueva_variable+thread);
 
  }
 
}
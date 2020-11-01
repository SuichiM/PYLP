#include <omp.h>
#include <iostream>

int main (){

int nthreads, thread;
int new_var = 777;

omp_set_num_threads(10); // ESTABLECE LA CANTIDAD DE HILOS
/*
 * Si se removemos la clausula `private` lo que va a pasar que las variables
 * `nthreads` y `thread` se definen como compartidas.
 */
 /*
  * Si una variable global con valor establecido se pasa por la clausula
  * `private` a una sección paralela, pierde el valor que tenia. 
  * Para inicializar con el valor que tenia hay que usar la clausula `firstprivate`.
  */
#pragma omp parallel private(nthreads, thread) firstprivate(new_var)
  {

  thread = omp_get_thread_num();

  nthreads = omp_get_num_threads();

  #pragma omp critical
    std::cout<<"Hola OpenMP soy el hilo: "<< thread <<" de "<<nthreads<<" que somos y la new_var es: "<< new_var + thread <<std::endl;

  }

}
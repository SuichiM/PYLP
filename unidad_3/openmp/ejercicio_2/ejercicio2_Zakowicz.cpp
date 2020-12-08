#include <omp.h>
#include <iostream>
using namespace std;

#define N 10
#define nthreads 4

int main (){

  int thread;

  omp_set_num_threads(nthreads);

  #pragma omp parallel private(thread)
  {
    thread = omp_get_thread_num();
    /*Indica que las iteraciones de un bucle for han de ser repartidas entre las distintas hebras.
    #pragma omp for schedule*/

    //#pragma omp for schedule (static,4)
    /*  Las iterciones son divididas en partes de tamaño indicado, y las partes
      se asignan a las hebras mediante round-robin en el orden del número de hebra.
    */

    //#pragma omp for schedule (dynamic,2)
    /*  Cada hebra ejecuta una parte de las iteraciones, luego pide otra parte 
      hasta que no queden trozos para su distribución.
    */

    //#pragma omp for schedule (guided)
    /*  Cada hebra ejecuta una parte de las iteraciones, a continuación pide otra parte 
      hasta que no queden trozos para su distribución.
      Las partes comienzan siendo grandes y se van reduciendo con forme a lo planificado.
    */

    #pragma omp for schedule (auto)
    /*La decisión de reparto es delegada al compilador o el sistema.*/

    for (int i = 0 ; i < N; i++){

      #pragma omp critical 
        cout<<"Soy el proceso "<<thread<<" y ejecutó la iteración "<<i<< endl;
    }

  }
}

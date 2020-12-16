#include <omp.h>
#include <iostream>
#include <time.h>
using namespace std;


#define nthreads 40 // cantidad de hilos que se ejecutaran

int main (){
                          
  int vector[nthreads];
  int totalMultiplos = 0;
  
  srand(time(NULL));
  // Se carga el vector de forma random
  printf("\nEl vector es: \n");
  for (int i = 0; i < nthreads; i++) {
      vector[i] = rand() % 100;
      printf("%d / ", vector[i]);
  }
  

  omp_set_num_threads(nthreads);
  #pragma omp parallel firstprivate(vector) reduction(+:totalMultiplos)  
  {
      int izquierda;
      int derecha;
      int thread;

      thread = omp_get_thread_num();

      if (thread == 0) { // Se realiza la operacion correspondiente dependiendo si la posicion del vector esta al inicio, final o en medio

        izquierda = 0;
        derecha = vector[thread + 1];

        } else if (thread == nthreads - 1) {

            izquierda = vector[thread - 1];
            derecha = 0;

            }else {

                izquierda = vector[thread - 1];
                derecha = vector[thread + 1];
                
            }
        // se verifica si la sumatoria del valor a su izquiera mas el valor a la derecha, es multiplo del valor en su posicion

      if (  (izquierda + derecha) % vector[thread] == 0  ) {

          totalMultiplos = 1;

      }
      


  }
    //Se informa el resultado total
  printf("\nEl total de multiplos es de: %d\n", totalMultiplos);
}
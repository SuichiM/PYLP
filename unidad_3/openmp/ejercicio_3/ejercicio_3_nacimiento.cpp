#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

#define N 10
#define nthreads 4

int main (){
  srand(time(NULL));
  int thread;
  int vector[nthreads];
  int limitVector = nthreads - 1;
  int totalMultiples = 0;

  // Carga aleatoria del vector e impresion de sus elementos
  cout << endl;
  cout << "VECTOR: " << endl;
  for (int i = 0; i < nthreads; i++) {
      vector[i] = rand() % 100;
      cout << vector[i] << " - ";
  }
  cout << endl;

  omp_set_num_threads(nthreads);
  #pragma omp parallel private(thread) firstprivate(limitVector, vector) reduction(+:totalMultiples)
  {
      int previous, next, sumNeighbors,isMultiple;
      thread = omp_get_thread_num();

      if (thread == 0) {
        previous = limitVector;
        next = thread + 1;
      }
      else if (thread == limitVector) {
        previous = thread - 1;
        next = 0;
      }
      else {
        previous = thread - 1;
        next = thread + 1;
      }
      
      sumNeighbors = vector[previous] + vector[next];
      isMultiple = sumNeighbors % vector[thread] == 0 ? true : false;
      #pragma omp critial
      {
        cout << endl;
        cout << "Soy el hilo " << thread << endl;
        cout << sumNeighbors << " % " << vector[thread] << " = " << sumNeighbors % vector[thread] << endl;
        cout << endl;
      }

      if (isMultiple) totalMultiples = 1;

  }

  cout << "La cantidad de multiplos es " << totalMultiples << endl;
}
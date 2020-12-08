#include <omp.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define nthreads 5

int main ()
{
  const int ARRAY_SIZE = 5;
  int thread;
  int vector[ARRAY_SIZE];
  int sizeVector = nthreads -1;
  int totalMultiplos = 0;
  srand (time(NULL));  // Inicializa el generador de números aleatorios.

  // Carga del vector de manera aleatoria
  cout << endl;
  cout <<" Vector "<< endl;
  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    vector[i] = rand()%29; // Números aleatorios entre 0 y 29
    cout << vector[i] << " - ";
  }
  cout << endl;  
    
  omp_set_num_threads(nthreads);
  #pragma omp parallel private(thread)firstprivate(sizeVector, vector) reduction(+:totalMultiplos)
  {
   int antes, despues, suma;
   thread = omp_get_thread_num();

   if (thread == 0){
       antes = sizeVector;
       despues = thread +1;
   }
   else
   if (thread == sizeVector){
       antes = thread - 1;
       despues = 0;
   }
   else
   antes = thread - 1;
   despues = thread + 1;

    suma = vector[antes] + vector[despues];
    if(suma % vector[thread] == 0)  
       totalMultiplos = 1;
  
    #pragma omp critical 
    {
      cout << endl;
      cout << "Soy el hilo " << thread << endl;
      cout << suma << " % " << vector[thread] << " = " << suma % vector[thread] << endl;
      cout << endl;
    }
  }  
  cout << "La cantidad de múltiplos es: " << totalMultiplos << endl;
}
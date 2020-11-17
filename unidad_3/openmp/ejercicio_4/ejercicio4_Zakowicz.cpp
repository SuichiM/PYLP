#include <omp.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define nthreads 2

int main ()
{
  int thread;
  int sizeVector = nthreads * 5 ; // El valor 5 es proporcionado en la consigna por la cátedra.
  srand (time(NULL));  // Inicializa el generador de números aleatorios.

  int vector1[sizeVector];
  int vector2[sizeVector];
  int total = 0;
  int producto = 0;

  // Carga de los vectores de manera aleatoria
  for (int i = 0; i < sizeVector; i++){
    vector1[i] = rand()%29; 
    vector2[i] = rand()%29;
  }

  // Se imprime vector 1
  cout << endl;
  cout <<" Vector 1 "<< endl;
  for (int i = 0; i < sizeVector; i++)
    cout << vector1[i] << " - ";
  cout << endl;

   // Se imprime vector 2
  cout << endl;
  cout <<" Vector 2 "<< endl;
  for (int i = 0; i < sizeVector; i++)
    cout << vector2[i] << " - ";
  cout << endl;
    
  omp_set_num_threads(nthreads);
  #pragma omp parallel for private(thread, producto) reduction(+:total)
  /* Utilizado para las cláusulas omp atomic y omp critical
  #pragma omp parallel for private(thread, producto) */
    for(int i = 0; i < sizeVector; i++){
      thread = omp_get_thread_num();
      producto = vector1[i] * vector2[i];
      total += producto;
    /*Utilizando la variable compartida total dentro de la cláusula omp atomic
    #pragma omp atomic
        total += producto;
    */
    #pragma omp critical 
    {
     /* Utilizando la variable compartida total dentro de la cláusula omp critical 
      producto = vector1[i] * vector2[i];
      total += producto;*/
      cout << endl;
      cout << "Soy el hilo: " << thread << " Iteración: " << i <<  endl;
      cout << " Producto: " << vector1[i] << " * " << vector2[i] << " = " << producto << endl;
      cout << endl;
    }
  }  
  cout << "La sumatoria total del producto es: " << total << endl;
}
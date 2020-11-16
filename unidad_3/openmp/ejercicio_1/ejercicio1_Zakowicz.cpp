// 1. Se compila (g++ -fopenmp ejercicio1_Zakowicz.cpp -o ejercicio1)
  // y se ejecuta el archivo (./ejercicio1)
#include <omp.h>
#include <iostream>

int main (){

// 4. Crear una variable con el valor de 777 y defirla dentro de la clausula `private`
// de la region paralela ¿Que pasa con su valor?. Su valor es 0.
int nuevaVariable = 777; 

int nthreads;
int thread;

// 2. Fija el número de hebras en secciones paralelas.
omp_set_num_threads(10);

// 3. Si se elimina la cláusula private, las variables pasan a ser compartidas
//  por todas las hebras en la región paralela.

// 5. Al utilizar la cláusula firstprivate. El valor de la variable es 777.
#pragma omp parallel private(nthreads, thread) firstprivate(nuevaVariable)
  {
  thread = omp_get_thread_num();

  nthreads = omp_get_num_threads();

  std::cout<<"Soy la hebra "<< thread <<" de "<<nthreads<<" que somos. El valor de la variable es: "<<nuevaVariable<<std::endl;

  }

}
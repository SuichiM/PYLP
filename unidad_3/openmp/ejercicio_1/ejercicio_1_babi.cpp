#include <omp.h>
#include <iostream>

//Para definir la cantidad de hilos
#define hilos 10

int main()
{

  int nthreads;
  int thread;
  int variable = 777;
  //punto 4: En caso que se pase esta variable dentro del #pragma omp parallel esta variable se define como compartida
  //siempre que no este dentro de la clausula private

  //Punto 2 para ejecutar por 10 Hilos
  omp_set_num_threads(hilos);

//Punto 3: Si le quito el private las variables puede ser modificadas por todos los procesos, porque serán compartidas.
//Punto 5: En caso de usar firstprivate toda la region dentro del omp parallel tendra la variable privada, pero inicializada
// con el valor que tiene actualmente (777).
#pragma omp parallel private(nthreads, thread) firstprivate(variable)
  {
    thread = omp_get_thread_num();

    variable = variable + thread;
    nthreads = omp_get_num_threads();

    std::cout << "Hola Mundo soy la hebra = " << thread << " de " << nthreads << " que somos. tengo la variable :" << variable << std::endl;
  }
}
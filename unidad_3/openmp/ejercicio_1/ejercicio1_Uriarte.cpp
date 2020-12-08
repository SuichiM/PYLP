#include <omp.h>
#include <iostream>

int main()
{

  int nthreads, thread;
  int var = 100;
  // establecemos la cantidad de hilos a lanzar

  omp_set_num_threads(5);

  // Si se saca la clausula "private" lo que va a pasar que las variables "nthreads" y "thread" se definen como compartidas.

  // Si una variable global con un valor establecido se pasa mediante la clausula "private" a la sección paralela, se pierde el valor que tenia.
  // Para inicializar con el valor que tenia hay que usar la clausula "firstprivate"

#pragma omp parallel private(nthreads, thread) firstprivate(var)
  {
    thread = omp_get_thread_num();

    nthreads = omp_get_num_threads();

#pragma omp critical
    std::cout << "Soy el hilo: " << thread << " de " << nthreads << " que somos y el valor de la nueva variable es: " << var + thread << std::endl;
  }
}
#include <omp.h>
#include <iostream>

int main(){
    
    int nthreads;
    int thread;

    omp_set_num_threads(10);
    
    int numero = 777;

    //Inicia ejecucion paralela, private-> c/hilo tiene su propio nthreads, thread (el contenido se borra)
    //con firstprivate no se borra el contenido inicial de la variable
    #pragma omp parallel private(nthreads, thread) firstprivate(numero)
    {
        thread = omp_get_thread_num();
        nthreads = omp_get_num_threads();

        #pragma omp critical //seccion critica
        {
            std::cout<<"Hola Mundo soy la hebra = "<< thread <<" de "<<nthreads<<" que somos"<<std::endl;
            std::cout<<"valor de la nueva variable: " << numero + thread << std::endl;
        }
    }
}
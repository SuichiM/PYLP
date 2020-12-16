#include <omp.h>
#include <iostream>

#define N 10
#define nthreads 4

int main (){
    int thread;
    omp_set_num_threads(nthreads);
    #pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();

        #pragma omp for schedule(static, 2)
        for (int i = 0 ; i < N; i++){
            #pragma omp critical
                std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
        }

    }
}
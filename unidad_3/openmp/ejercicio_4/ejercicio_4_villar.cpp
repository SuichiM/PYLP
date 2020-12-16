#include <omp.h>
#include <iostream>
using namespace std;

#define NH 5 //Numero de Hilos a ejecutar

int main(){
    int v1[NH*5] = {1,6,1,1,1,3,1,1,1,1,28,4,1,4,7,1,1,1,7,5,11,1,4,5,9};
    int v2[NH*5] = {1,2,2,5,1,7,4,1,4,4,3,5,10,4,7,12,2,2,7,5,11,2,4,5,9};
    int totalR, totalC, totalA = 0;

    omp_set_num_threads(NH);
    #pragma omp parallel reduction(+:totalR)
    {
        int thread = omp_get_thread_num();

        #pragma omp for schedule(auto)
        for(int i=0; i < NH*5; i++){
            totalR+= v1[i] * v2[i]; //Sumando usando reduction
            
            #pragma omp critical
            totalC+= v1[i] * v2[i]; //Sumando una variable compartida con critical

            #pragma omp atomic
            totalA+= v1[i] * v2[i]; //Sumando una variable compartida con atomic
        }
        
    }
    printf("\ntotalR: %d", totalR);
    printf("\ntotalA: %d", totalA);
    printf("\ntotalC: %d\n", totalC);
}
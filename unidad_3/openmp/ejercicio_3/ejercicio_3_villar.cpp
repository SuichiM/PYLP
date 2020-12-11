#include <omp.h>
#include <iostream>
using namespace std;

#define NH 20 //Numero de Hilos a ejecutar

int main(){
    int totalMultiplos = 0;
    int v[NH] = {14,62,14,25,17,5,10,1,54,45,28,4,1,4,7,12,12,23,20,5};
    
    omp_set_num_threads(NH);
    #pragma omp parallel firstprivate(v) reduction(+:totalMultiplos)
    {
        int thread, suma;
        thread = omp_get_thread_num();

        if(thread != 0 && thread != NH-1){ //Si no estamos en ninguno de los extremos
            suma = v[thread-1] + v[thread+1];
        }else{ //extremos, simulando lista circular
            if(thread == 0)
                suma = v[NH-1] + v[thread+1];
            if(thread == NH-1)
                suma = v[thread-1] + v[0];
        }
        //se comprueba si es multiplo
        if (suma % v[thread] == 0){
            #pragma omp critical
            printf("Soy el hilo %d: calculo %d mod %d  = 0  - Es multiplo \n",thread, suma, v[thread]);
            totalMultiplos = 1;
        }else{
            #pragma omp critical
            printf("Soy el hilo %d: calculo %d mod %d != 0  - No es multiplo \n",thread, suma, v[thread]);
        }        
    }
    printf("Cantidad de múltiplos: %d\n",totalMultiplos);
}
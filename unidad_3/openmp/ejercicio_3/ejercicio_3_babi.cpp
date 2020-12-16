#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define NH 15

int main()
{
    int hilo, totalMultiplos = 0;
    int vector[NH];
    srand(time(NULL));
    printf("Cargar vector.");
    for (int i = 0; i < NH; i++)
    {
        vector[i] = rand() % 20 + 1;
        printf("\n %d - %d ", i, vector[i]);
    }

    omp_set_num_threads(NH);
#pragma omp parallel private(hilo), firstprivate(vector) reduction(+ \
                                                                   : totalMultiplos)
    {
        hilo = omp_get_thread_num();

        int miNum = vector[hilo];
        int numIzq, numDer, suma;

        if (hilo != 0 && hilo != NH - 1)
        {
            numIzq = vector[hilo - 1];
            numDer = vector[hilo + 1];
        }
        else
        {
            if (hilo == 0)
            {
                numIzq = 0;
                numDer = vector[hilo + 1];
            }

            if (hilo == NH - 1)
            {
                numIzq = vector[hilo - 1];
                numDer = 0;
            }
        }

        //suma de valores
        suma = numIzq + numDer;

        //comprobacion de si es multiplo
        if (suma % miNum == 0)
        {
            //#pragma omp critical
            printf("\nSoy %d \tcalculando %d mod %d = 0 \ty SI es multiplo.", hilo, suma, miNum);
            totalMultiplos = 1;
        }
        else
        {
            //#pragma omp critical
            printf("\nSoy %d \tcalculando %d mod %d != 0 \ty NO es multiplo.", hilo, suma, miNum);
        }
    }

    printf("\ntotalMultiplos: %d\n", totalMultiplos);
}
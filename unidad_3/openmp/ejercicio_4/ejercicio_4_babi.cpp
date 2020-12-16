#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define NH 7  //Numero de Hilos
#define CPH 5 //Cantidad Por Hilo

int main()
{
    int hilo, producto, totalR = 0, totalA = 0, totalC = 0, numeroTotal = NH * CPH;
    int vector1[numeroTotal], vector2[numeroTotal];
    //inicializo el randomizer
    srand(time(NULL));
    //Cargar los vectores
    printf("Datos Cargados:");
    for (int i = 0; i < numeroTotal; i++)
    {
        vector1[i] = rand() % 20 + 1;
        vector2[i] = rand() % 20 + 1;
        printf("\n%d = Vector1: \t%d \t| Vector2: \t%d", i, vector1[i], vector2[i]);
    }

    omp_set_num_threads(NH);

#pragma omp parallel private(hilo, producto), firstprivate(vector1, vector2, numeroTotal) reduction(+ \
                                                                                                    : totalR)
    {
        hilo = omp_get_thread_num();
        producto = 0;
        int calculo = 0;

#pragma omp for schedule(static)
        for (int i = 0; i < numeroTotal; i++)
        {
            //realizo el calculo
            calculo = vector1[i] * vector2[i];
            //sumo a mi variable local
            producto += calculo;
            //sumo a la variablo global totalA pero usando atomic
#pragma omp atomic
            totalA += calculo;
            //sumo a la varbiale global totalC usando Critical
#pragma omp critical
            totalC += calculo;
        }
        //Seteo el resultado del productor escalar en la variable totalR usada para la reduccion
        totalR = producto;

        printf("\nValor del producto del hilo %d es de:\t%d", hilo, producto);
    }

    printf("\nReduction: resultado final producto escalar: \t%d", totalR);
    printf("\nAtomic: resultado final producto escalar: \t%d", totalA);
    printf("\nCritical: resultado final producto escalar: \t%d", totalC);
    printf("\n\n");
}
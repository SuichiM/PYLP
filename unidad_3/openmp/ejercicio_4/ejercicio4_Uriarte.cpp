#include <omp.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

#define N 5
#define nthreads 8

int main()
{
    int thread;
    int tamañoVector = N * nthreads;

    int v1[tamañoVector];
    int v2[tamañoVector];
    int total = 0;
    int producto;

    // cargo los vectores
    for (int i = 0; i < tamañoVector; i++)
    {
        v1[i] = rand() % 100;
        v2[i] = rand() % 100;
    }

    //imprimo los vectores 1 y 2
    cout << endl;
    cout << "vector 1= " << endl;
    for (int i = 0; i < tamañoVector; i++)
    {
        cout << v1[i] << " - ";
    }
    cout << endl;

    cout << endl;
    cout << "vectore 2= " << endl;
    for (int i = 0; i < tamañoVector; i++)
    {
        cout << v2[i] << " - ";
    }
    cout << endl;

    omp_set_num_threads(nthreads);
#pragma omp parallel for private(thread, producto) reduction(+ \
                                                             : total)
    for (int i = 0; i < tamañoVector; i++)
    {
        thread = omp_get_thread_num();
        producto = v1[i] * v2[i];
        total += producto;
#pragma omp critical
        cout << "Proceso" << thread << "Iteracion" << i << v1[i] << " * " << v2[i] << " = " << producto << endl;
    }

    cout << "Total= " << total << endl;
}
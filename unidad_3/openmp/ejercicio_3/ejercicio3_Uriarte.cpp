#include <omp.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define N 10
#define nthreads 4

int main()
{
    int thread;
    int vector[nthreads];
    int total = 0;
    int limiteVector = nthreads - 1;

    // cargo el vector y imprimo
    cout << endl;
    cout << "vector= " << endl;
    for (int i = 0; i < nthreads; i++)
    {
        vector[i] = rand() % 100;
        cout << vector[i] << " - ";
    }
    cout << endl;

    omp_set_num_threads(nthreads);
#pragma omp parallel private(thread) firstprivate(limiteVector, vector) reduction(+ \
                                                                                  : total)
    {
        int anterior, siguiente, sumaValProximos, multiplo;
        thread = omp_get_thread_num();

        if (thread == 0)
        {
            anterior = limiteVector;
            siguiente = thread + 1;
        }
        else if (thread == limiteVector)
        {
            anterior = thread - 1;
            siguiente = 0;
        }
        else
        {
            anterior = thread - 1;
            siguiente = thread + 1;
        }

        sumaValProximos = vector[anterior] + vector[siguiente];
        multiplo = sumaValProximos % vector[thread] == 0 ? true : false;

        //zona critica
#pragma omp critial
        {
            cout << endl;
            cout << "Hilo numero: " << thread << endl;
            cout << sumaValProximos << " / " << vector[thread] << " = " << sumaValProximos % vector[thread] << endl;
            cout << endl;
        }

        if (multiplo)
            total = 1;
    }

    cout << "Existen " << total << "multiplos." << endl;
}
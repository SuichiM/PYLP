#include <omp.h>
#include <iostream>

#define NH 13

int main (){
    int hilo, totalMultiplos = 0;
    int vectorGlobal[NH] = {10,21,29,40,13,21,29, 20, 12, 28, 33, 11, 5};

    printf("Vector global:\n");
    for (int i = 0 ; i < NH; i++)
    {
        printf(" %d -",vectorGlobal[i]);
    }
    printf("\n\n");

    /*RESULTADO EN MI CONSOLA
        Vector global:
        10 - 21 - 29 - 40 - 13 - 21 - 29 - 20 - 12 - 28 - 33 - 11 - 5 -
    */


    //Seteamos la cantidad de hilos
    omp_set_num_threads(NH);
    #pragma omp parallel private(hilo), firstprivate(vectorGlobal) reduction(+:totalMultiplos)
    {
        hilo = omp_get_thread_num();

        //Obtenemos los valores
        int valorHiloCentro = vectorGlobal[hilo];
        int valorHiloIzquierda, valorHiloDerecha, sumaIzquierdaDerecha;
        
        if(hilo != 0 && hilo != NH-1){
            valorHiloIzquierda = vectorGlobal[hilo-1];
            valorHiloDerecha = vectorGlobal[hilo+1];

        }else{
            if (hilo == 0){
                valorHiloIzquierda = vectorGlobal[NH-1];
                valorHiloDerecha = vectorGlobal[hilo+1];
            }

            if (hilo == NH-1){
                valorHiloIzquierda = vectorGlobal[hilo-1];
                valorHiloDerecha = vectorGlobal[0];
            }
        }

        //Sumamos los extremos
        sumaIzquierdaDerecha = valorHiloIzquierda + valorHiloDerecha;

        //Comprobamos si la suma de los extremos el múltiplo del valor del centro
        if (sumaIzquierdaDerecha % valorHiloCentro == 0){
            #pragma omp critical
            printf("Proceso %d: %d | %d | %d  --  %d + %d = %d  --  %d mod %d  = 0  -- MULTIPLO \n\n",hilo,valorHiloIzquierda, valorHiloCentro, valorHiloDerecha, valorHiloIzquierda, valorHiloDerecha, sumaIzquierdaDerecha, sumaIzquierdaDerecha, valorHiloCentro);
            totalMultiplos = 1;
        }else{
            #pragma omp critical
            printf("Proceso %d: %d | %d | %d  --  %d + %d = %d  --  %d mod %d != 0  -- NO MULTIPLO \n\n",hilo,valorHiloIzquierda, valorHiloCentro, valorHiloDerecha, valorHiloIzquierda, valorHiloDerecha, sumaIzquierdaDerecha, sumaIzquierdaDerecha, valorHiloCentro);
        }
    }

    printf("Cantidad de múltiplos: %d\n\n",totalMultiplos); // 4-> La variable tiene la cantidad de multiplos porque usamos la clausula reduction

    /*RESULTADO DE MI CONSOLA
        Vector global:
        10 - 21 - 29 - 40 - 13 - 21 - 29 - 20 - 12 - 28 - 33 - 11 - 5 -

        Proceso 1: 10 | 21 | 29  --  10 + 29 = 39  --  39 mod 21 != 0  -- NO MULTIPLO  

        Proceso 0: 5 | 10 | 21  --  5 + 21 = 26  --  26 mod 10 != 0  -- NO MULTIPLO    

        Proceso 9: 12 | 28 | 33  --  12 + 33 = 45  --  45 mod 28 != 0  -- NO MULTIPLO  

        Proceso 2: 21 | 29 | 40  --  21 + 40 = 61  --  61 mod 29 != 0  -- NO MULTIPLO  

        Proceso 7: 29 | 20 | 12  --  29 + 12 = 41  --  41 mod 20 != 0  -- NO MULTIPLO  

        Proceso 12: 11 | 5 | 10  --  11 + 10 = 21  --  21 mod 5 != 0  -- NO MULTIPLO   

        Proceso 4: 40 | 13 | 21  --  40 + 21 = 61  --  61 mod 13 != 0  -- NO MULTIPLO  

        Proceso 8: 20 | 12 | 28  --  20 + 28 = 48  --  48 mod 12  = 0  -- MULTIPLO     

        Proceso 5: 13 | 21 | 29  --  13 + 29 = 42  --  42 mod 21  = 0  -- MULTIPLO     

        Proceso 6: 21 | 29 | 20  --  21 + 20 = 41  --  41 mod 29 != 0  -- NO MULTIPLO  

        Proceso 10: 28 | 33 | 11  --  28 + 11 = 39  --  39 mod 33 != 0  -- NO MULTIPLO 

        Proceso 11: 33 | 11 | 5  --  33 + 5 = 38  --  38 mod 11 != 0  -- NO MULTIPLO   

        Proceso 3: 29 | 40 | 13  --  29 + 13 = 42  --  42 mod 40 != 0  -- NO MULTIPLO  

        Cantidad de múltiplos: 2
    */
}
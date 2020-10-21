#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rango, size, lng;
    int sumaParcial = 0;
    int sumaGlobal = 0;
    MPI_Init(&argc, &argv); //Inicializamos la estructura de comunicación paralela entre procesos

    MPI_Comm_rank(MPI_COMM_WORLD, &rango); //Obtenemos (en rango) el rango del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_size(MPI_COMM_WORLD, &size); //Obtenemos (en size) el tamaño del comunicador MPI_COMM_WORLD

    //Definimos los vectores y su tamaño
    lng = size * 5;

    int vectorGlobal1[lng];
    int vectorGlobal2[lng];

    int vectorLocal1[5];
    int vectorLocal2[5];

    //El proceso 1 carga los dos vectores
    if (rango == 0){
        for (int i = 0; i < lng; i++){
            vectorGlobal1[i] = i;
            vectorGlobal2[i] = (lng-1) - i;

        }
        //Imprimo los vectores globales
        printf("Vector Global 1 \n");
        for (int i = 0; i < lng; i++){
            printf("%d - ",vectorGlobal1[i]);
        }
        printf("\n");  
        /*
            Vector Global 1
            0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 
        */

        printf("Vector Global 2 \n");
        for (int i = 0; i < lng; i++){
            printf("%d - ",vectorGlobal2[i]);
        }
        printf("\n"); 
        /*
            Vector Global 2
            19 - 18 - 17 - 16 - 15 - 14 - 13 - 12 - 11 - 10 - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 - 0 -
        */
    }

    //Distribuimos los vectores
    MPI_Scatter(
    &vectorGlobal1[0],   //Lo que envio   
    5,                  //Cuanto envio  
    MPI_INT,            //Tipo de dato de envio  
    &vectorLocal1[0],    //Donde recibo
    5,                  //Cuanto recibo
    MPI_INT,            //Tipo de dato que recibo
    0,                  //Proceso que envia (El proceso 0 distribuye)
    MPI_COMM_WORLD      //Por cual comunicador envio
    );

    MPI_Scatter(
    &vectorGlobal2[0],   //Lo que envio   
    5,                  //Cuanto envio  
    MPI_INT,            //Tipo de dato de envio  
    &vectorLocal2[0],    //Donde recibo
    5,                  //Cuanto recibo
    MPI_INT,            //Tipo de dato que recibo
    0,                  //Proceso que envia (El proceso 0 distribuye)
    MPI_COMM_WORLD      //Por cual comunicador envio
    );

    //Imprimo los vectores locales
    /*
    printf("Vector local 1 del proceso %d \n",rango);
    for (int i = 0; i < 5; i++){
        printf("%d - ",vectorLocal1[i]);
    }
    printf("\n");  

    printf("Vector local 2 del proceso %d \n",rango);
    for (int i = 0; i < 5; i++){
        printf("%d - ",vectorLocal2[i]);
    }
    printf("\n");
    */

    //Calculamos el resultado parcial
    for (int i = 0; i < 5; i++){
        sumaParcial += vectorLocal1[i] * vectorLocal2[i];
    }

    printf("Resultado parcial del proceso %d es: %d \n", rango, sumaParcial);

    /*
        Resultado parcial del proceso 0 es: 160
        Resultado parcial del proceso 1 es: 410
        Resultado parcial del proceso 2 es: 410
        Resultado parcial del proceso 3 es: 160
    */




    //Unimos los resultados locales con los globales usando MPI_Reduce
    MPI_Reduce(
    &sumaParcial,   //Lo que envio 
    &sumaGlobal,    //Donde lo recibo
    1,              //Tamaño de lo que envio
    MPI_INT,        //Tipo de lo que se envia (reduce)
    MPI_SUM,        //Operacion que se realiza
    0,              //Proceso receptor
    MPI_COMM_WORLD  //Comunicador
    );

    //Imprimimos el resultado global
    if (rango == 0){
        printf("Resultado final en el proceso %d es: %d \n", rango, sumaGlobal);
    }


    /* IMPRESION EN MI COSOLA:
            Vector Global 1
            0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 
            Vector Global 2
            19 - 18 - 17 - 16 - 15 - 14 - 13 - 12 - 11 - 10 - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 - 0 - 
            Resultado parcial del proceso 0 es: 160
            Resultado parcial del proceso 3 es: 160 
            Resultado parcial del proceso 1 es: 410
            Resultado parcial del proceso 2 es: 410
            Resultado final en el proceso 0 es: 1140
    */


    MPI_Finalize(); //Finalizamos la estructura de comunicación paralela entre procesos
}
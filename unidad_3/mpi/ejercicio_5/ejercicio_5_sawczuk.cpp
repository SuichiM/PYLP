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

    /* ANALISIS
        Vector global:          0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 -

        Procesos + 2:                   2         -          3        -           4            -            5           -

        Vector global nuevo:    1 - 0 - 1 - 0 - 1 - 0 - 1 - 0 - 0 - 1 -  0 -  0 -  1 -  0 -  0 -  1 -  0 -  0 -  0 -  0 - 
    */

    //Definimos los vectores y su tamaño
    lng = size * 5;

    int vectorGlobal[lng];

    int vectorLocal[5];

    //El proceso 0 carga del vector
    if (rango == 0){
        for (int i = 0; i < lng; i++){
            vectorGlobal[i] = i;

        }
        //Imprimo el vector global
        printf("Vector Global \n");
        for (int i = 0; i < lng; i++){
            printf("%d - ",vectorGlobal[i]);
        }
        printf("\n");  
        /*
            Vector Global
            0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 
        */

    }

    //Distribuimos el vector
    MPI_Scatter(
    &vectorGlobal[0],   //Lo que envio   
    5,                  //Cuanto envio  
    MPI_INT,            //Tipo de dato de envio  
    &vectorLocal[0],    //Donde recibo
    5,                  //Cuanto recibo
    MPI_INT,            //Tipo de dato que recibo
    0,                  //Proceso que envia (El proceso 0 distribuye)
    MPI_COMM_WORLD      //Por cual comunicador envio
    );


    //Imprimo el vector local antes de procesar
    printf("Vector local del proceso %d antes de calcular: \n",rango);
    for (int i = 0; i < 5; i++){
        printf("%d - ",vectorLocal[i]);
    }
    printf("\n");  

    /*
        Vector local del proceso 0 antes de calcular:
        0 - 1 - 2 - 3 - 4 -
        Vector local del proceso 1 antes de calcular:
        5 - 6 - 7 - 8 - 9 -
        Vector local del proceso 2 antes de calcular:
        10 - 11 - 12 - 13 - 14 -
        Vector local del proceso 3 antes de calcular: 
        15 - 16 - 17 - 18 - 19 -
    */


    //Reemplazamos el vector local
    for (int i = 0; i < 5; i++){
        /*
            Si el vectorLocal es multiplo de rango+2
                reemplazo por 1
            sino
                reemplazo por 0
        */
        if (vectorLocal[i] % (rango+2) == 0){
            vectorLocal[i] = 1;
        }else{
            vectorLocal[i] = 0;
        }
    }

    //Imprimo el vector local despues de calcular
    printf("Vector Local del proceso %d despues de calcular:\n", rango);
    for (int i = 0; i < 5; i++){
        printf("%d - ",vectorLocal[i]);
    }
    printf("\n");  
    /*
        Vector Local del proceso 0 despues de calcular:
        1 - 0 - 1 - 0 - 1 -
        Vector Local del proceso 1 despues de calcular:
        0 - 1 - 0 - 0 - 1 -
        Vector Local del proceso 2 despues de calcular:
        0 - 0 - 1 - 0 - 0 -
        Vector Local del proceso 3 despues de calcular:
        1 - 0 - 0 - 0 - 0 -
    */


    //Reemplazamos el vector fuente con los nuevos resultados (Gather unimos)
    MPI_Gather(
    &vectorLocal[0],    //Lo que envio 
    5,                  //Cuanto envio 
    MPI_INT,            //Cuanto envio
	&vectorGlobal[0],   //Donde se unen los datos 
    5,                  //Cuantos elementos se esperan recibir 
    MPI_INT,            //De que tipo se espera recibir 
    0,                  //En el proceso 0 se unen los datos
	MPI_COMM_WORLD
    );

    //Imprimimos el resultado global
    if (rango == 0){
        printf("Vector global con los datos nuevos: \n");
        for (int i = 0; i < lng; i++){
            printf("%d - ",vectorGlobal[i]);
        }
        printf("\n");
    }


    /* IMPRESION EN MI COSOLA:
            Vector local del proceso 3 antes de calcular: 
            15 - 16 - 17 - 18 - 19 -
            Vector Local del proceso 3 despues de calcular:
            1 - 0 - 0 - 0 - 0 -
            Vector Global
            0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 -
            Vector local del proceso 0 antes de calcular:
            0 - 1 - 2 - 3 - 4 -
            Vector Local del proceso 0 despues de calcular:
            1 - 0 - 1 - 0 - 1 -
            Vector local del proceso 2 antes de calcular:
            10 - 11 - 12 - 13 - 14 -
            Vector Local del proceso 2 despues de calcular:
            0 - 0 - 1 - 0 - 0 -
            Vector local del proceso 1 antes de calcular:
            5 - 6 - 7 - 8 - 9 -
            Vector Local del proceso 1 despues de calcular:
            0 - 1 - 0 - 0 - 1 -
            Vector global con los datos nuevos:
            1 - 0 - 1 - 0 - 1 - 0 - 1 - 0 - 0 - 1 - 0 - 0 - 1 - 0 - 0 - 1 - 0 - 0 - 0 - 0 -
    */

    MPI_Finalize(); //Finalizamos la estructura de comunicación paralela entre procesos
}
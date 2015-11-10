/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : main.c
* Creation Date : 09-11-2015
* Last Modified : Mon 09 Nov 2015 02:32:53 PM CST
* Created By : root

KNOW LEARN        .==.
C LANGUAGE       ()''()-.
      .---.       ;--; /
    .'_:___". _..'.  __'.
    |__ --==|'-''' \'...;
   [  ]  :[|       |---\
    |__| I=[|     .'    '.
    / / ____|     :       '._
   |-/.____.'      | :       :
  /___\ /___\      '-'._----'
_._._._._._._._._._._._._._._._._._._._._.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

#define N 500000

/*paralelizame esta*/
int main()
{
    /* ------- Secuencial -------*/
    int A[N], B[N], S[N];
    srand(time(NULL));
    clock_t t;
    int l;
    /* 3 etapas
     * Inicializacion */
    for(int i = 0; i < N; ++i)
    {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
        S[i] = 0;
    }

    /*
     * Computo
     */

    t = clock();
    for(int k = 0; k < N; ++k)
        S[k] = A[k] + B[k];

    /*
     * Visualizacion de resultados
     */

    for(int j = 0; j < N; ++j)
        printf("[%7d] %3d + %3d = %4d\n", j, A[j], B[j], S[j]);

    t = clock() - t;

    printf ("Tarde %f segundo(s), para acabar secuencial\n", (float)t/CLOCKS_PER_SEC);

    /* ------- parte paralela -------*/

    /* 3 etapas
     * Inicializacion */
     #pragma omp parallel private(l)
     {
         printf("Hilo %d de %d\n", omp_get_thread_num(), omp_get_num_threads());
        
        #pragma omp for
        for(l = 0; l < N; ++l)
        {
            A[l] = rand() % 100;
            B[l] = rand() % 100;
            S[l] = 0;
        }

       /*
        * Computo
        */
    #pragma omp parallel private(l)
    {
        t = clock();
        #pragma omp for
        for(l = 0; l < N; ++l)
            S[l] = A[l] + B[l];
    }
        /*
        * Visualizacion de resultados
        */

        for(l = 0; l < N; ++l)
            printf("[%7d] %3d + %3d = %4d\n", l, A[l], B[l], S[l]);

        t = clock() - t;

        printf ("Tarde %f segundo(s), para acabar paralela\n", (float)t/CLOCKS_PER_SEC);
    }
    
    return 0;
}

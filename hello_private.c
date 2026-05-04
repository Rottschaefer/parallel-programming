#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){

    printf("Fora = %d\n", omp_in_parallel());

    int i, n=7;
    int a;

    #pragma omp parallel for private(a)
        for ( i = 0; i < n; i++)
        {
            a += i;
            printf("Thread %d tem um valor de a = %d para i = %d", omp_get_thread_num(), a, i);

        }


        
    
    return 0;
}
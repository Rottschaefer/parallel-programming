#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){

    printf("Fora = %d\n", omp_in_parallel());

    int i, n=7;
    int a[n];

    #pragma omp parallel for shared(a)
        for (i = 0; i < n; i++)
        {
            a[i] = i+1;
        }

    #pragma omp parallel for shared(a)
        for ( i = 0; i < n; i++)
        {
            a[i] += i;
        }

        printf("No prog principal");

        for ( i = 0; i < n; i++)
        {
            printf("a[%d] = %d\n", i, a[i]);
        }

        
    
    return 0;
}
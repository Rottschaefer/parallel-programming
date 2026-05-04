#include <stdio.h>
#include <omp.h>

int main(){

    printf("Fora = %d\n", omp_in_parallel());

    int nthreads, tid;



    #pragma omp parallel private(nthreads, tid) num_threads(4)
    {       
        tid = omp_get_thread_num();
        printf("Olá da thread %d\n", tid);
        // printf("Dentro = %d\n", omp_in_parallel());

        if(tid == 0){
            nthreads = omp_get_num_threads();
            printf("Número de threads = %d\n", nthreads);
        }
    }
    return 0;
}
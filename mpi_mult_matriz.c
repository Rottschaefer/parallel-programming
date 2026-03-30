#include <stdio.h>
#include <stdlib.h>
#include "mpi.h" 

void mxv(int n, double* A, double* b, double* c);

int main(int argc, char *argv[]) { /* mpi_mxv.c  */
double *A,*Aloc, *b,*c;
/* matriz m x n por um vetor de dimensão n */
int i, j, m, n;                     
int meu_ranque, num_procs, raiz=0;
double start, finish, loc_elapsed, elapsed;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
   
   if (meu_ranque == 0) {
     printf("Por favor entre com m: \n");
     scanf("%d",&m);
     printf("\n");
     printf("Por favor entre com n: \n");
     scanf("%d",&n);
     printf("\n");
   }
   

   MPI_Bcast(&n, 1, MPI_INT, raiz, MPI_COMM_WORLD);
   MPI_Bcast(&m, 1, MPI_INT, raiz, MPI_COMM_WORLD);

   int linhas_por_processo = m/num_procs;


    if (meu_ranque == 0) {
        printf("Valor de m: %d e  n: %d \n", m,n);
        A=(double*) malloc(m*n*sizeof(double));
        Aloc=(double *)malloc(m*n*sizeof(double));
        b=(double*) malloc(n*sizeof(double));
        c=(double*) malloc(m*sizeof(double));
     } else {
        Aloc=(double *) malloc(n*linhas_por_processo*sizeof(double));
        b=(double*) malloc(n*sizeof(double));
        c=(double*) malloc(linhas_por_processo*sizeof(double));
     }    

     if (meu_ranque == 0) {
         printf("Atribuindo valor inicial à matriz A e ao vetor b\n");

         for (j = 0; j < n; j++)
              b[j] = 2.0;
         for (i = 0; i < m; i++)
              for (j = 0; j < n; j++)
                  A[i*n + j] = (double) i;
     }
   //   /* Difunde o vetor b para todos os processos */
      MPI_Bcast(&b[0],n,MPI_DOUBLE,raiz, MPI_COMM_WORLD);

   //   /* Distribui as linhas da matriz A entre todos os processos */

      MPI_Scatter(A, n*linhas_por_processo, MPI_DOUBLE, Aloc, n*linhas_por_processo, MPI_DOUBLE,raiz, MPI_COMM_WORLD);
      
      start = MPI_Wtime();

      for (int i = 0; i < linhas_por_processo; i++)
      {
         (void) mxv(n, &Aloc[i*n], b, &c[i]);
      }
      
      MPI_Gather(c, linhas_por_processo, MPI_DOUBLE, c, linhas_por_processo, MPI_DOUBLE, raiz, MPI_COMM_WORLD);
   
      finish = MPI_Wtime();
      loc_elapsed = finish-start;
      MPI_Reduce(&loc_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);  

      if (meu_ranque == 0) {
         printf("Tempo total = %e\n", elapsed);

         printf("\n");
         
         printf("Matriz A\n\n");

         for (i = 0; i < m; i++){
               printf("\n");
              for (j = 0; j < n; j++)
                  printf("  %f", A[i*n + j]);
            }

         printf("\n\n");
         
         
         printf("Vetor b\n\n");

          for (j = 0; j < n; j++) printf(" %f", b[j]);
         printf("\n\n");
         

         //Print vetor c
         for (int i = 0; i < m; i++)
         {
            printf("%f\n", c[i]);
         }
         
      }

      if(meu_ranque == 0){
         free(A);
      }
      free(Aloc);
      free(b);
      free(c);
     
      MPI_Finalize();
      return(0);
}

void mxv(int n, double* A, double* b, double* c) {
int j;
      *c = 0.0;
      for (j = 0; j < n; j++)
           *c += A[j]*b[j];
}
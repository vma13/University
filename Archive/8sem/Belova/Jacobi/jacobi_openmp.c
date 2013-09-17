#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define  Max(a,b) ((a)>(b)?(a):(b))
#define  L  500
#define  ITMAX 500
int i,j,it,k;
double t1, t2;
double eps;
double MAXEPS = 0.5;
double A[L][L], B[L][L];
int main(int an, char **as)
{ 
  //printf("JACOBI STARTED\n");
  t1=omp_get_wtime();

 for(i=0; i<=L-1; i++)
   for(j=0; j<=L-1; j++)
     {

         A[i][j]=5.;
         B[i][j]=1.+i+j;
       }
     

 for(it=1; it<=ITMAX; it++)
   {
     eps= 0.;    
     for(i=1; i<=L-2; i++)
       for(j=1; j<=L-2; j++)
         {                  
           eps = Max(fabs(B[i][j]-A[i][j]),eps);
           A[i][j] = B[i][j];
         }
#pragma omp parallel num_threads(2)
#pragma omp parallel for private(i)
     for(i=1; i<=L-2; i++)
       //#pragma omp parallel for private(j)
       for(j=1; j<=L-2; j++)
         #pragma omp
       {
         B[i][j] = (A[i-1][j]+A[i+1][j]+
                    A[i][j-1]+A[i][j+1])/4.;
       }
   
     t2=omp_get_wtime();
     
     // printf( "it=%4i   eps=%f\n", it,eps);
     if (eps < MAXEPS) break;
   }
 printf("Время работы: %lfs\n", (t2 - t1));
  return 0;
}




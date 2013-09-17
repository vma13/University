#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
#include<time.h>
#include <sys/time.h>

#define M 20
#define N 5
#define  Max(a,b) ((a)>(b)?(a):(b))
#define  L  2000
#define  ITMAX 2000
int i,j,it,k;
double eps;
double MAXEPS = 0.5;
double A[L][L], B[L][L];
int proc_rank;
int proc_num;
double rt, t1, t2;
int main(int argc, char** argv)
{

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD,&proc_num);
  MPI_Comm_rank(MPI_COMM_WORLD,&proc_rank);
  
  for(i=0; i<=L-1; i++)
    for(j=0; j<=L-1; j++){
      A[i][j]=0.;
      B[i][j]=1.+i+j;
    }
   
  t1 = MPI_Wtime();
  for(it=1; it<=ITMAX; it++){
    eps= 0.;
    for(i=1; i<=L-2; i++)
      for(j=1; j<=L-2; j++)
        {
          eps = Max(fabs(B[i][j]-A[i][j]),eps);
          A[i][j] = B[i][j];
        }
    for(i=1; i<=L-2; i++)
      for(j=1; j<=L-2; j++){
        B[i][j] = (A[i-1][j]+A[i+1][j]+A[i][j-1]+A[i][j+1])/4.;
    MPI_Alltoall(B,M,MPI_DOUBLE,B,M,MPI_DOUBLE,MPI_COMM_WORLD);
      }
    t2 = MPI_Wtime();
       
       
       
    if (eps < MAXEPS) break;
      
     
  }
  rt = t2 - t1;
  printf( "time=%lf\n", rt);
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}


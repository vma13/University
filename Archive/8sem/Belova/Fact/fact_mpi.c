#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
  double t1, t2;
  int rank, size;
  int i, n;
  double X = 1.0;

  n = 160;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  t1 = MPI_Wtime();
  for(i = 1; i <= n; i++) {
    MPI_Bcast(&X, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    X *= i;
  }
  t2 = MPI_Wtime();
  printf("time = %lf\n", t2 - t1);
  printf("Result: %.0lf\n", X);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0; 
}


  
  

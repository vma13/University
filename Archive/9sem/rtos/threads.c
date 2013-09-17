#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> 
#include <errno.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>

#define N 600

int A[N][N], B[N][N], C[N][N];

inline int rand_number(int max) {
  return rand()%max;
}

int init_matrix_a() {
  int i, j;
   
    for( i = 0; i < N; i++) {
      for( j = 0; j < N; j++)
        A[i][j] = rand_number(50);
  }
  return EXIT_SUCCESS;
}

int init_matrix_b() {
  int i, j;
   
    for( i = 0; i < N; i++) {
      for( j = 0; j < N; j++)
        B[i][j] = rand_number(100);
  }
  return EXIT_SUCCESS;
}

int white_data(){
  double det;
  FILE *f;

    det = rand_number(10);
    printf("matrix determinant == %lf\n", det);
    f = fopen("out", "w");
    fwrite(&det, 1, sizeof(det), f);
    fclose(f);
  return EXIT_SUCCESS;
}

int mult_matrix(void* arg) {
  int i, j, sum, k;
 
 while(1) {
  init_matrix_a();
  init_matrix_b();
    for( i = 0; i < N; i++) {
      for( j = 0; j < N; j++) {
        sum = 0;
        for( k = 0; k < N; k++) {
          sum += A[i][k]*B[k][j];
        }
        C[i][j] = sum;
      }
    }
    printf("mul matrix done\n");
    white_data();
  }
  return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
  srand( time(NULL) );
  pthread_t t1, t2;
  pthread_attr_t tattr;
  struct sched_param param;
  int max;
  
  max = 10;//sched_get_priority_min( SCHED_RR )+5;
  param.sched_priority = max;

  pthread_attr_init(&tattr);
  pthread_attr_setinheritsched(&tattr, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&tattr, SCHED_RR);
  pthread_attr_setschedparam (&tattr, &param);
  pthread_create(&t1, &tattr, (void*)mult_matrix, NULL);
 pthread_create(&t2, &tattr, (void*)mult_matrix, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return EXIT_SUCCESS;
}

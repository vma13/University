#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> 
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sched.h>

#define N 10

int A[N][N], B[N][N], C[N][N];
int semid;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;

void terminate(int sig_value) {
  semctl(semid, 0, IPC_RMID, 0);
  exit( EXIT_SUCCESS );
}

void test(size_t value) {
  if( value == -1 ) {
    semctl(semid, 0, IPC_RMID, 0);
    puts( strerror(errno) );
    exit( EXIT_FAILURE );
  }
}

void block_sem(int semnum, int sem_cmd) {
  struct sembuf s;
  s.sem_num = semnum;
  s.sem_op  = sem_cmd;
  s.sem_flg = 0;
  test( semop(semid, &s, 1) );
}

inline int rand_number(int max) {
  return rand()%max;
}

int init_matrix_a(void* arg) {
  int i, j;
   
  while( 1 ) {
    pthread_mutex_lock(&m1);
    for( i = 0; i < N; i++) {
      for( j = 0; j < N; j++)
        A[i][j] = rand_number(50);
    }
    printf("init matrix A finish\n");
    block_sem(0, -1);
  }
  return EXIT_SUCCESS;
}

int init_matrix_b(void* arg) {
  int i, j;
   
  while( 1 ) {
    pthread_mutex_lock(&m2);
    for( i = 0; i < N; i++) {
      for( j = 0; j < N; j++)
        B[i][j] = rand_number(100);
    }
    printf("init matrix B finish\n");
    block_sem(0, -1);
  }
  return EXIT_SUCCESS;
}

double determinant(int **a, int n) {
  int i, j, j1, j2;
  double det;
  int **m = NULL;
  
  if( n == 2 )
    det = a[0][0]*a[1][1] - a[1][0]*a[0][1]; 
  else {
    det = 0;
    for( j1 = 0; j1 < n; j1++) {
      m = (int**)malloc((n-1)*sizeof(int *));
      for( i = 0; i < n-1; i++)
	m[i] = (int*)malloc((n-1)*sizeof(int));
      for( i = 1; i < n; i++) {
	j2 = 0;
	for( j = 0; j < n; j++) {
	  if( j == j1 )
	    continue;
	  m[i-1][j2] = a[i][j];
	  j2++;
	}
      }
      det += pow(-1.0, 1.0+j1+1.0)*a[0][j1]*determinant(m, n-1);
      for( i = 0; i < n-1; i++)
	free( m[i] );
      free( m );
    }
  }
  return det;
}

int white_data(void* arg){
  double det;
  FILE *f;

  while(1) {
    pthread_mutex_lock(&m3);
    det = determinant(C, N);
    printf("matrix determinant == %u\n", (int)det);
    f = fopen("out", "w");
    fwrite(&det, 1, sizeof(det), f);
    test( fclose(f) );
    block_sem(0, -1);
  }
  return EXIT_SUCCESS;
}

int mult_matrix(void* arg) {
  int i, j, sum, k;
 
  while( 1 ) {
    block_sem(0, 0);
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
    pthread_mutex_unlock(&m3);
    pthread_mutex_unlock(&m1);
    pthread_mutex_unlock(&m2);
    block_sem(0, 1);
    block_sem(0, 1);
    block_sem(0, 1);
  }
  return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
  signal(SIGINT, terminate);
  signal(SIGTERM, terminate);
  srand( time(NULL) );
  pthread_t t1, t2, t3, t4;
  key_t k;
  pthread_attr_t tattr;
  struct sched_param param;
  int max;
  
  max = sched_get_priority_max( SCHED_RR );
  param.sched_priority = max;

  pthread_attr_init(&tattr);
  pthread_attr_setinheritsched(&tattr, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&tattr, SCHED_RR);
  pthread_attr_setschedparam (&tattr, &param);

  test( k = ftok(*argv, 0) );
  test( semid = semget(k, 1, 0666 | IPC_CREAT) );
  block_sem(0, 1);
  block_sem(0, 1);
  pthread_mutex_lock(&m3);
  
  pthread_create(&t1, &tattr, (void*)init_matrix_a, NULL);
  pthread_create(&t2, &tattr, (void*)init_matrix_b, NULL);
  pthread_create(&t3, &tattr, (void*)mult_matrix, NULL);
  pthread_create(&t4, &tattr, (void*)white_data, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);
  return EXIT_SUCCESS;
}

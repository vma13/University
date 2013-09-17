#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SHM_SIZE 300
#define ITER 6

int shmid;
int semid;

int check(int retval){
  if(retval == -1){
    printf(strerror(errno));
    exit(1);
  }
  return 0;
}

void on_int(int signum){
  shmctl(shmid, IPC_RMID, NULL);
  semctl(semid, 0, IPC_RMID, 0);
  printf("Выход по сигналу\n");
  kill(0, SIGTERM);
}

int block_sem(int semid, int semnum, int sem_cmd){
  struct sembuf s;
  s.sem_num=semnum;
  s.sem_op=sem_cmd;
  s.sem_flg=0;
  check(semop(semid, &s, 1));
  return 0;
}


int child(int shmid, int semid){
  int* mem;
  int i;

  check((int)(mem=shmat(shmid, NULL, 0)));


   int j=0;
  for(i=0;i<ITER; i++){
    block_sem(semid, 1, 0);
    const char * a=(const char *)(j);
   *mem=*mem+1;
    printf("2) %d\n", *mem);
    sleep(1);
    block_sem(semid, 1, 1);
    block_sem(semid, 2, -1);
  }

  return 0;
}

int child1(int shmid, int semid){
  int* mem;
  int i;

  check((int)(mem=shmat(shmid, NULL, 0)));

  for(i=0;i<ITER; i++){
    block_sem(semid, 2, 0);
    *mem=*mem+1;
    printf("3) %d\n", *mem);
    sleep(1);
    block_sem(semid, 2, 1);
    block_sem(semid, 0, -1);
  }

  return 0;
}

int main(int argc, char** argv){
  int* mem;
  key_t key;
  int i;

  check(key=ftok(argv[0], 0));
  check(shmid=shmget(key, SHM_SIZE, 0666 | IPC_CREAT));
  check(semid=semget(key, 3, 0666 | IPC_CREAT));

  block_sem(semid, 1, 1);
  block_sem(semid, 2, 1);

  signal(SIGINT, on_int);
  
  if(!fork()){
    child(shmid, semid);
    exit(0);
  }
  if(!fork()){
			child1(shmid, semid);
			exit(0);
		}
    
  check((int)(mem=shmat(shmid, NULL, 0)));
  * mem=0;
  

  for(i=0;i<ITER;i++){
    block_sem(semid, 0, 0);
    *mem=*mem+1;
    printf("1) %d\n", *mem);
    sleep(1);
    block_sem(semid, 0, 1);
    block_sem(semid, 1, -1);
  }

  wait(NULL);
  /*
  check(shmctl(shmid, IPC_RMID, NULL));
  check(semctl(semid, 0, IPC_RMID, 0));
  */
  
  return 0;
}
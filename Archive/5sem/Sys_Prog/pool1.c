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

#define SHM_SIZE 20
#define ITER 6

int check(int retval, char * reason){
  if(retval == -1){
    printf(reason, strerror(errno));
    exit(1);
  }
  return 0;
}

int block_sem(int semid, int semnum, int sem_cmd){
  struct sembuf s;
  s.sem_num=semnum;
  s.sem_op=sem_cmd;
  s.sem_flg=0;
  check(semop(semid, &s, 1), "semop");
  return 0;
}

int child(int num, int shmid, int semid){
  int* a;
  int i;
  
  check((int)(a=shmat(shmid, NULL, 0)), "shmat");
  
  while(1){
    block_sem(semid, num, 0);
    a[num]=a[num]*a[num+10];
    sleep(1);
    block_sem(semid, num, 1);
    block_sem(semid, 10, -1);
  }
  
  return 0;
}

int main(int argc, char** argv){
  int shmid;
  int semid;
  int num;
  int* a;
  key_t key;
  int i;

  check(key=ftok(argv[0], 0), "ftok");
  check(shmid=shmget(key, SHM_SIZE, 0666 | IPC_CREAT), "shmget");
  check(semid=semget(key, 11, 0666 | IPC_CREAT), "semget");

  for(num=0; num<10; num++){
  block_sem(semid, i, 1);
  }
  
  
  for(i=0; i<10; i++){
  if(!fork()){
    child(num, shmid, semid);
    exit(0);
  }
  }
  check((int)(a=shmat(shmid, NULL, 0)), "shmat in main");
  * a=0;
 
  
  for(i=0; i<20; i++){
    a[i]=i+1;
  }

  for(i=0; i<10; i++){
    block_sem(semid, i, -1);
  }
  block_sem(semid, 10, -10);
  
  for(i=0; i<20; i++){
    printf("%d", a[i]);
  }
  
  check(shmctl(shmid, IPC_RMID, NULL), "shmctl");
  check(semctl(semid, 0, IPC_RMID, 0), "semctl");
  
  wait(NULL);
  return 0;
}

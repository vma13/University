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
#include <math.h>

int shmid, shmid1, semid, n;

int check(int retval, char* reason){
  if(retval == -1){
    printf("%s: %s\n", reason, strerror(errno));
    exit(1);
  }
  return 0;
}

void initial(int signum){
  int i;
  shmctl(shmid, IPC_RMID, NULL);
  shmctl(shmid1, IPC_RMID, NULL);
  semctl(semid, 0, IPC_RMID, 0);
  for(i=0;i<(n/2);i++){
    wait(NULL);
  }
  exit(0);
}

int block_sem(int semid, int semnum, int sem_cmd){
  struct sembuf s;
  s.sem_num=semnum;
  s.sem_op=sem_cmd;
  s.sem_flg=0;
  check(semop(semid, &s, 1), "semop in block_sem");
  return 0;
}

int child(int num, int shmid, int semid){
  float* mem;
  int* wire1;
  float  h, d;
  
  check((int)(mem=shmat(shmid, NULL, 0)), "shmat in child");
  check((int)(wire1=shmat(shmid1, NULL, 0)), "shmat in 2 child");
  
  while(1){
    block_sem(semid, num, 0);
    h=mem[(wire1[num])];
    d=mem[(wire1[num+n/2])];
    if(h>d){
      mem[(wire1[num])]=d;
      mem[(wire1[num+n/2])]=h;
    }
    block_sem(semid, num, 1); 
    block_sem(semid, (n/2), 1);
  }
  
  return 0;
}

int main(int argc, char** argv){
  int num;
  float* mem;
  int* wire1;
  key_t key;
  int k;
  int i, j;
  
  scanf("%d ", &n);
  if((n&(n-1))!=0){
    printf("Число не является степенью двойки.\n");
    exit(0);
  }

  check(key=ftok(argv[0], 0), "ftok in main");
  check(shmid=shmget(key, n, 0666 | IPC_CREAT), "shmget");
  check(shmid1=shmget(IPC_PRIVATE, n, 0666 | IPC_CREAT), "shmget2");
  check(semid=semget(key, (n/2+1), 0666 | IPC_CREAT), "semget");
  
  double nn = (double)n;
  double l = log(nn)/(log(2));
  int wire[n/2][2];
  double mmem[n];
  double iter, len, m, start, mm;
  int kk;
  
  for(num=0; num < (n/2); num++){
    block_sem(semid, num, 1);
  }
  
  for(num=0; num<(n/2); num++){
    if(!fork()){
      child(num, shmid, semid);
      exit(0);
    }
  }
  
  signal(SIGINT, initial);
  
  check((int)(mem=shmat(shmid, NULL, 0)), "shmat in main");
  *mem=0;
  
  for(k=0; k<n; k++){
    scanf("%lf", &mmem[k]);
  }
  
  for(k=0; k<n; k++){
    mem[k]=mmem[k];
  }
  printf("\n");
  
  check((int)(wire1=shmat(shmid1, NULL, 0)), "shmat in main2");
  
  for(iter=0; iter<l; iter++){
    len=nn/(pow(2, (iter+1)));
    kk=0;
    for(m=0; m<(pow(2, iter)); m++){
      start=(m)*(nn/pow(2, iter));
      for(mm=start; mm<(start+(nn/(pow(2, (iter+1))))); mm++){
        wire[kk][0]=mm;
        wire[kk][1]=mm+len;
	kk++;
      }
    }
    
    printf("Input: ");
    for(k=0; k<n; k++){
      printf("%lf ", mem[k]);
    }
    printf("\n");
    
    for(num=0; num<(n/2); num++){
      wire1[num]=wire[num][0];
      wire1[num+n/2]=wire[num][1];
    }
    
    for(num=0; num<(n/2); num++){
      block_sem(semid, num, -1);
    }
    
    block_sem(semid, (n/2), -(n/2));
    
    printf("Output: ");
    for(i=0; i<n; i++){
      printf("%lf ", mem[i]);
    }
    printf("\n\n");
    
    sleep(1);
    
  }
  kill(0, SIGINT);
  
  return 0;
}

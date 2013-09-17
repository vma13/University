#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>



int main() {
   struct sembuf{
  short sem_num;
  short sem_op;
  short sem_flg;    
  };
  char file[]="newproc.c";
  int key=ftok(file,0);
  semget(key,0,666|IPC_CREAT);
  struct sembuf mybuf;
  struct sembuf* semnew(char s[]){
  unsigned n;  
  if (s=="a")n=1;
  if (s=="d")n=-1;
  if (s=="z")n=0;    
  mybuf.sem_num=0;
  mybuf.sem_op=n;
  mybuf.sem_flg=0;
  semop(key,&mybuf,n);
  }
  
  int chanel[2];
  if (pipe(chanel)) {
    strerror(errno);
    exit(1);
  }
  char wbuf[100];
  scanf("%s", wbuf);
  wbuf[strlen(wbuf)] = '\n';
  char rbuf[100];
  memset(&rbuf, 0, 100);
  if (fork()) {
    semnew("z");
    semnew("a");
    write(chanel[1], wbuf, 100);
    printf("%s write ", wbuf);
    wait(NULL);
    semnew("d");
  } else {
    semnew("z");
    semnew("a");
    read(chanel[0], rbuf, 100);
    printf("%sread ", rbuf);
    semnew("d");
  }
  printf("%s", rbuf);
  close(chanel[0]);
  close(chanel[1]);
  return 0;
}

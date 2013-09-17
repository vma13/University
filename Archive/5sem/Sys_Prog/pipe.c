#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(){
  int chanel[2];
  if (pipe(chanel)){
    strerror(errno);
    exit(1);
  }
  char file[] = "pipe.c";
  int key = ftok(file, 0);
  shmget(key, 0, 0666 | IPC_CREAT);
  i = char *shmat(shmget, 0, 0);
  char wbuf[100];
  scanf("%s", wbuf);
  wbuf[strlen(wbuf)] = '\n';
  char rbuf[100];
  memset(&rbuf, 0, 100);
  if (fork()){
      write(chanel[1], i, 100);    
      wait(NULL);
      printf("write");
      puts(wbuf);
    }else{
    read(chanel[0], i, 100);
    printf("read");
      puts(rbuf);
    }
    close(chanel[0]);
    close(chanel[1]);
    return 0;
  }


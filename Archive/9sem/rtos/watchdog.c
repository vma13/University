#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>

int wd(void *argv) {
  int pid, fd, i;
  int determinant, num; 
  determinant = -1;
  pid = vfork();
  if( pid == -1 )
    perror("can't create child process");
  if( pid == 0 ) {
    execl("./threads", "./threads", NULL);
  }
  else {
    while( 1 ){
      usleep( 3000000 );
      fd = open("out", O_RDWR);
      read(fd, &num, sizeof(num));
      close( fd );
      if( determinant == num ) { 
        kill(pid, SIGTERM);
        printf("Killed\n");
        i = 0;
        while( i < 900000000) {
          i++;
        }
        printf("\n!!!!\n");
        pid = vfork();
        if( pid == -1 )
          perror("can't create child process");
        if( pid == 0 ) {
          execl("./threads", "./threads", NULL);
        }
      }
      else {
        determinant = num;
      }
    }
  }	
}

int main(int argc, char **argv) {
  pthread_t t1;
  pthread_attr_t tattr;
  struct sched_param param;
  int max;
  
  param.sched_priority =  50;

  pthread_attr_init(&tattr);
  pthread_attr_setinheritsched(&tattr, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&tattr, SCHED_RR);
  pthread_attr_setschedparam (&tattr, &param);
  pthread_create(&t1, &tattr, (void*)wd, NULL);
  pthread_join(t1, NULL);
  return 0;
}

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

int pid;

void func(void *argv) {
  struct sched_param param;

  while( 1 ) {
    printf("work\n");
    sleep(1);
    printf("***%d-->%d\n", sched_getparam(pid, &param), param.sched_priority);
  }
}

int main() {
  pthread_t t1;
  pthread_attr_t tattr;
  struct sched_param param;
  int max;
  
  max = 0;//sched_get_priority_max( SCHED_RR );
  param.sched_priority = max;

  printf("%d\n", max);
  pthread_attr_init(&tattr);
  //pthread_attr_setstacksize(&tattr, DEFAULT_PTHREAD_STACK_SIZE);
  pthread_attr_setinheritsched(&tattr, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&tattr, SCHED_RR);
  pthread_attr_setschedparam (&tattr, &param);
  pid = pthread_create(&t1, NULL, (void*)func, NULL);

  sched_setscheduler(pid, SCHED_RR, &param); 
  printf("\n%d-->%d\n", sched_getparam(pid, &param), param.sched_priority);

  param.sched_priority = max;
  printf("\n%d-->%d\n", sched_getparam(pid, &param), param.sched_priority);
  pthread_join(t1, NULL);
  return 0;
}

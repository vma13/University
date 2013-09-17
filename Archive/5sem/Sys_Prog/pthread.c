#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

pthread_mutex_t mutex;
pthread_t tid;
int count_hit = 0;

int thread(){
  pthread_mutex_lock(&mutex);
  //count_hit++;
  //sleep(2);
  pthread_mutex_unlock(&mutex);
  while(1){
    pthread_mutex_lock(&mutex);
    if(count_hit%2 > 0){
      printf("2\n");
      count_hit++;
      pthread_mutex_unlock(&mutex);
      break;
    }
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  pthread_exit(NULL);
  return 0;
}

int main(int argc, char **argv){
  int ret;
  if((ret = pthread_mutex_init(&mutex, NULL)) != 0){
    printf("Error in mutex creating\n");
    return 1;
  }
  pthread_mutex_lock(&mutex);
  if((ret = pthread_create(&tid, NULL, (void*)thread, NULL)) != 0){
    printf("Error in thread creating");
    return 1;
  }
  pthread_mutex_unlock(&mutex);
  while(1){
    pthread_mutex_lock(&mutex);
    if(count_hit%2 == 0){
      printf("1\n");
      count_hit++;
    }
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  pthread_join(tid, NULL); //freze until enought
  pthread_exit(NULL); //main enought, thread is still working
  return 0;
}
  


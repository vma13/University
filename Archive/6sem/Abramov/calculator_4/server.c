#include <sys/socket.h>	
#include <netinet/in.h>	
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>

#define SIZE 1000
#define ADRESS_SIZE 30
#define DATA_SIZE 30

#ifndef PROCESS_LIMIT
#define PROCESS_LIMIT 5
#endif

typedef struct {
  pthread_t pid;
  pthread_mutex_t mutex;
} process_data;
process_data* process[PROCESS_LIMIT];


char line[SIZE];			
double res = 0.0;
_Bool flag = 0, disp = 0;
char address[ADRESS_SIZE], sign, cur_num[DATA_SIZE];
int sockfd, newsockfd;
pthread_mutex_t main_lock;

int cur_style = 0;

void add_char(char *str, char ch) {
  int i = strlen(str);
  if( i < DATA_SIZE ) str[i] = ch;
}

#include "calc.h"

void perform(void) {
  switch( sign ) {
    case '-':
      res -= (double)atof(cur_num);
      break;
    case '+':
      res += (double)atof(cur_num);
      break;
    case '*':
      res *= (double)atof(cur_num);
      break;
    case 'D':
      res /= (double)atof(cur_num);
      break;
  }
  bzero(cur_num, sizeof(cur_num));
  disp = 0;
}

void address_process(void) {
  int j;
  while( 1 ) {
    j = find_pid(pthread_self());
    printf("Process %d locked\n", j);
    pthread_mutex_lock(&(process[j]->mutex));
    printf("Process %d unlocked\n", j);
    get_address(line);
    printf("ADRESS:: %s\n", address);
    if( strncmp(address, "index.html", 10) == 0 ) send_html();
    else if( strncmp(address, "style=", 6) == 0 ) {
      cur_style = (int)(address[6]-'0');
      send_html();
    }
    else if( strlen(address) == 1 ) {
      if( isdigit(address[0]) || address[0] == 'P' ) {
        disp = 1;
        if( address[0] == 'P' ) add_char(cur_num, '.');
        else add_char(cur_num, address[0]);
      }
      else  {
        switch( address[0] ) {
        case '-':
        case '+':
        case 'D':
        case '*':
          if( flag ) perform();
          else {
            flag = 1;
            res = (double)atof(cur_num);
            bzero(cur_num, sizeof(cur_num));
            disp = 0;
          }
        sign = address[0];
        break;
        case '=':
          flag = 1;
          perform();
          sign = address[0];
          break;
        case 'C':
          flag = 0;
          res = 0.0;
          disp = 0;
          bzero(cur_num, sizeof(cur_num));
          break;
        }
      }
      send_html();
    } else send_file(address);
    close(newsockfd);
    pthread_mutex_unlock(&main_lock);
  }
}


void initialize_thread(void) {
  int i;
  for( i = 0; i < PROCESS_LIMIT; i++ )
    process[i] = (process_data*)malloc(sizeof(process_data));
  pthread_mutex_init(&main_lock, NULL);
  
  //pthread_mutex_lock(&main_lock);
  for( i = 0; i < PROCESS_LIMIT; i++ ) {
    pthread_mutex_init(&(process[i]->mutex), NULL);
    pthread_mutex_lock(&(process[i]->mutex));
    pthread_create(&(process[i]->pid), NULL, (void*)address_process, NULL);
  }
}

int find_free_thread(void) {
  static int cur_thread = 0;
  if( (cur_thread+1) == PROCESS_LIMIT ) cur_thread = 0;
  else cur_thread++;
  return cur_thread;
}

int find_pid(unsigned long int id) {
  int i;
  for( i = 0; i < PROCESS_LIMIT; i++ )
    if( process[i]->pid == id ) return i;
  return i;
}


int main(int argc, char **argv) {
  int optval = 1, clilen, i;			
  struct sockaddr_in servaddr, cliaddr; 
  initialize_thread();
    
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(51000);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  listen(sockfd, 5);
  //pthread_mutex_unlock(&main_lock);
  while( 1 ) {
    printf("Main process locked\n");
    pthread_mutex_lock(&main_lock);
    clilen = sizeof(cliaddr);
    bzero(line, sizeof(line));
    newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, (socklen_t*) &clilen);
    read(newsockfd, line, SIZE-1);
    i = find_free_thread();
    printf("Main process %d unlocked\n", i);
    pthread_mutex_unlock(&(process[i]->mutex));
  }
  for( i = 0; i < PROCESS_LIMIT; i++ )
    pthread_join(process[i]->pid, NULL);
  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>

#define NOT_FOUNDE -1

typedef struct process {
  int execution_time;
  int deadline;
  int time_left;
  int next_deadline;
  int prev_deadline;
  _Bool start;
} process;

int search(process *p, int size, int step) {
  int i, min, index_min;
  _Bool flag = 1;
  
  for( i = 0; i < size; i++) {
    if( p[i].prev_deadline < step && p[i].next_deadline-1 < step ) {
      printf(" Deadleine %d process\n", i+1);
      while(1);
      exit( EXIT_SUCCESS );
    }
    if( p[i].prev_deadline <= step && step <= p[i].next_deadline-1 ) {
      if( flag ) {
        min = p[i].next_deadline;
        index_min = i;
        flag = 0;
      }
      if( min > p[i].next_deadline ) {
        min = p[i].next_deadline;
        index_min = i;
      }
      if( min == p[i].next_deadline && p[i].start == 1 ){
        min = p[i].next_deadline;
        index_min = i;
      }
    }
  }
  return !flag ? index_min : NOT_FOUNDE;
}

void rebuild(process *p) {
  p->start = 0;
  p->time_left = p->execution_time;
  p->next_deadline += p->deadline;
  p->prev_deadline += p->deadline;
}

int main(int argc, char **argv) {
  int size, iteration, i, next_process;
  process *p;
  
  scanf("%d %d", &iteration, &size);
  p = (struct process*)malloc(size*sizeof(struct process));
  for( i = 0; i < size; i++) {
    scanf("%d", &p[i].execution_time);
    scanf("%d", &p[i].deadline);
    
    p[i].time_left = p[i].execution_time;
    p[i].next_deadline = p[i].deadline;
    p[i].prev_deadline = 0;
    p[i].start = 0;
  }
  
  for(i = 0; i < iteration; i++) {
    next_process = search(p, size, i);
    if( next_process == NOT_FOUNDE )
      putchar('*');
    else {
      printf("%d", next_process+1);
      p[next_process].start = 1;
      p[next_process].time_left -= 1;
      if( p[next_process].time_left == 0 )
        rebuild( &p[next_process] );
    }
  }
  putchar('\n');
  while(1);
  return EXIT_SUCCESS;
}

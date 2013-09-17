#ifndef _STACK_H_
#define _STACK_H_
#include <stdio.h>
#include <malloc.h>

struct stack{
  GLfloat x, y;
  GLfloat angle;
  struct stack *next;
};

struct stack *head = NULL;
struct stack *tail = NULL;

struct stack* push(GLfloat x, GLfloat y, GLfloat angle) {
  struct stack *p = (struct stack*)malloc(sizeof(struct stack));
  p->x =x;
  p->y = y;
  p->angle = angle;
  p->next = head;
  return head = p;
}

struct stack* pop(void) {
  if( head == NULL ) return NULL;
  struct stack *p = head;
  head = head->next;
  free(p);
  return p;
}

void print1(void) {
  struct stack *p = head;
  while( p != NULL ) { 
    printf("x = %f\ny = %f\nangle = %f\n", p->x, p->y, p->angle);
    p = p->next;
  }
}

#endif

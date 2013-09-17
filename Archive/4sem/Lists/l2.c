#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct l2 {
  
  struct l2* next;
  struct l2* prev;
  int key;
}l2;

struct l2* head = NULL;

struct l2* tail = NULL;


struct l2* insert_head(int key){
  struct l2* p;
  if((p=(struct l2*)malloc(sizeof(struct l2)))==NULL){
    printf("Segmentation fault\n");
    exit(1);
  }
  p->key=key;
  p->next=head;
  p->prev=NULL;
  if(p->next!=NULL){
    p->next->prev=p;
  }
  head=p;
  if(tail==NULL){
    tail = p;
  }
  return p;
}

struct l2* insert_tail(int key){
  struct l2* p;
  if(head!=NULL){
    p=head;
    while(p->next!=NULL){
      p=p->next;
    }
    if((p->next=(struct l2*)malloc(sizeof(struct l2)))==NULL) {
            printf("Segmentation fault\n");
            exit(1);
    }
    
    p->next->key=key;
    p->next->next=NULL;
    p->next->prev=p;
    tail = p->next;
    return p->next;
  }else{
    insert_head(key);
    return head;
  }
}

struct l2 *insert_after(struct l2 *ptr, int key) {
  if(ptr == NULL)
    return insert_head(key);
  struct l2 *p;
  if((p = (struct l2*) malloc(sizeof(struct l2))) == NULL) {
    printf("Segmentation fault\n");
    exit(0);
  }
  p->key = key;
  if(ptr->next != NULL)
    ptr->next->prev = p;
  else tail = p;
  p->next = ptr->next;
  p->prev = ptr;
  ptr->next = p;
  return p;
}

struct l2 *remove_key(int key) {
  if( head != NULL ) {
    l2 *p, *ptr;
    if( head->key == key ) {
      p = head->next;
      free(head);
      head = p;
      if( head == NULL ) 
        tail = NULL;
      else head->prev = NULL;
      return;
    }
    for( p = head; p->next != NULL; p = p->next ) {
      if( p->next->key == key ) {
        ptr = p->next->next;
        free(p->next);
        p->next = ptr;
        if( p->next != NULL ) 
          p->next->prev = p;
        else tail = p;
        return;
      }
    }
  }
}

struct l2 *remove_all(int key) {
  if( head != NULL ) {
    l2 *p, *ptr;
    while( head->key == key ) {
      p = head->next;
      free(head);
      head = p;
      if( head != NULL ) head->prev = NULL;
      else {
        tail = NULL;
        return;
      }
    }
    for( p = head; p->next != NULL; ) {
      if( p->next->key == key ) {
        ptr = p->next->next;
        free(p->next);
        p->next = ptr;
        if( p->next != NULL ) 
          p->next->prev = p;
      } else  p = p->next;
    }
    tail = p;
  }
}

void clear(){
    l2 *p = head, *ptr;
    while(p) {
      ptr = p;
      p = p->next;
      free(ptr);
      head = p;
      }
      head = NULL;
      tail = NULL;
    }

void print(void){
  struct l2* p;
  for(p=head;p!=NULL;p=p->next){
    printf("%d\n", p->key);
  }
}

void print2(void){
  struct l2* p;
  if(head==NULL) return;
  for(p=head;p->next!=NULL;p=p->next);
  for(;p!=NULL;p=p->prev){
    printf("%d\n", p->key);
  }
}

int main(void){
  insert_head(1);
  insert_head(3);
  insert_head(4);
  insert_after(head, 2);
  remove_all(4);
    remove_key(2);
  print();
  printf("\n");
  print2();
  clear();
  return 0;
}

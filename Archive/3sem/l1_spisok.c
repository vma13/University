#include <stdio.h>
#include <malloc.h>

struct l1 {
  int key;
  struct l1 *next;
};

struct l1 *head = NULL;

void print_l1(void);
struct l1 *insert(int key); //Create new element of list and place it in increment order
void remove_l1(int key); //Find element with key and delete it
void remove_all(int key); //Remove all elements with key
struct l1 *insert_head(int key); //Create an element with key and place it in head
struct l1 *insert_tail(int key);
struct l1 *insert_after(struct l1 *p, int key);

int main() {
  insert_head(3);
  insert_tail(4);
  insert(2);
  insert(1);
  insert(5);
  print_l1();
  return 0;
}

void print_l1(void) {
  struct l1 *p;
  for(p = head; p != NULL; p = p->next)
    printf("%d\n", p->key);
}

struct l1 *insert_head(int key) {
  struct l1 *p = (struct l1*) malloc(sizeof(struct l1));
  p->key = key;
  p->next = head;
  head = p;
  return p;
}

struct l1 *insert_tail(int key) {
  if(head == NULL) {
    head = (struct l1*) malloc(sizeof(struct l1));
    head->key = key;
    return head;
  }
  struct l1 *p = head;
  struct l1 *n = (struct l1*) malloc(sizeof(struct l1));
  n->key = key;
  while(p->next != NULL)
    p = p->next;
  p->next = n;
  return n;
}

struct l1 *insert(int key) {
  if(head == NULL) {
    head = (struct l1*) malloc(sizeof(struct l1));
    head->key = key;
    return head;
  }
  struct l1 *p = head;
  struct l1 *prev = NULL;
  while((p->key < key) && (p->next != NULL)) {
    prev = p;
    p = p->next;
  }
  if(prev == NULL) {
    struct l1*n = insert_head(key);
    return n;
  }
  if(p->next == NULL) {
    struct l1 *n = insert_tail(key);
    return n;    
  }
  struct l1 *n = (struct l1*) malloc(sizeof(struct l1));
  n->key = key;
  prev->next = n;
  n->next = p;
  return n;
}

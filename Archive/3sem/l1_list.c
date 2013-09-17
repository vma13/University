#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int val;
  struct node *next;
} node;

void l1_initialize(node **head);
void l1_finalize(node *head);
void l1_print(node *head);
void l1_insert(node *head, int value);
void l1_delete(node *head, int value);

int main(void)
{
  node *head;
  l1_initialize(&head);
  l1_print(head); l1_insert(head, 3);
  l1_print(head); l1_insert(head, 5);
  l1_print(head); l1_delete(head, 5);
  l1_print(head); l1_insert_after(head, 45);
  l1_print(head); l1_insert_head(50)
  l1_print(head);
  l1_finalize(head);

  return 0;
}

void l1_initialize(node **head)
{
  *head = (node *) malloc(sizeof(node));
  (*head)->next = NULL;
}

void l1_insert(node *head, int value)
{
  node *last = head;
  while (last->next)
    last = last->next;
  node *new = (node *) malloc(sizeof(node));
  new->val = value;
  new->next = NULL;
  last->next = new;
}

void l1_print(node *head)
{
  if (head->next == NULL) {
    printf("[]\n");
    return;
  }
  node *cur;
  putchar('[');
  for (cur = head->next; cur != NULL; cur = cur->next) {
    printf("%d", cur->val);
    if (cur->next != NULL)
    printf(", ");
  }
  printf("]\n");
}

void l1_delete(node *head, int value){
  node *prev,*cur;
  prev=cur=head;
  while(cur->val!=value){
    prev=cur;
    cur=cur->next;
  }
  prev->next=cur->next;
  free(cur);
}

void l1_insert_after(node *head, int value){
  node *prev;
  node *p1 = prev -> next;
  if(prev < key)
    prev -> next -> key = key;
    prev -> next -> next = p1;
}

void l1_insert_head(int value){
  node *new -> next = head;
  head -> key;
}
  

void l1_finalize(node *head)
{
  free(head);
}

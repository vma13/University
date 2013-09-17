#include <stdio.h>

int main(){
	void remove(int key);
	void remove_all(int key);
	struct l1 * insert(int key);
	void printf_l1(void);
        return 0;
}

struct l1{
 int key;
  struct l1 * next;
}
  struct l1 * head;
head = NULL;
  void printf_l1(void){
    struct l1 * p;
    for(p = head; p != NULL; p = p -> next)
      printf("%d\n", p -> key);
  }
	
struct l1 * insert_head(int key){
  struct l1 * last = head;
  while(last -> next)
    last = last -> next;
  struct l1 * new;
  new -> key = key;
  new -> next = NULL;
  last -> next = new;
  return new;
}

/*struct l1 * insert_tail(int key){

}

struct l1 * insert_after(struct l1 * p){

}

void insert(key){

}*/
void remove(int key){
  int value;
  previous = key;
  key = head;
  while(current -> key != value){
    previous = current;
    current = current -> next;
  }
  previous -> next = current -> next;
}
		
void remove_all(int key){
  previous = key = head;
  while(current -> key)
    current = NULL;
  current = current -> next;
  previous -> next = current -> next;
}


				 
	/*#include <stdio.h>
#include <iostream.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//stek
struct stek {int value; struct stek *next;};

//pushing
stek *pushing(stek *st, int val){
 stek *f, *g = new stek;
  g->value = val;
  g->next = NULL;
  if (st->next == NULL) {st = g;}
  else{
   for (f = st; f->next != 0; f = f->next){
	f->next = g;
	}
   }
 return st;
  }

//popping
stek *popping(stek *st){
 stek *s, *q = new stek;
 int i;
 i = 0;
 if (st == NULL) {cout<<"\n Error: stek pust";}
 else {
  for (q = st; i != 1; q = q->next){
   if (q->next == NULL) {
    i = 1;
    s = q;
    delete st;
    }
   else {break;}
  }
 }
 return s;
}

////////////////
//prosmotr spiska
void scan (stek *st) // zagolovok spiska
{
	stek *p = new stek;
for (p = st; p != NULL; p = p->next)
	 printf ("%d ", *p);
		printf ("\n");
}
////////////////

void main(){
 int n;
 stek *ST = new stek;
 cout<<"\nEnter pls. : ";
 cin>>n;
 pushing(ST, n);
 cout<<"\n N ="<<n;
 scan(ST);

}






void push(stack *top)
{
     stack *tmp=new stack();
         int value;
         cout<<"Enter the value: ";
         cin>>value;
         tmp->value=value;
     if(!top)
         top=tmp;
     else
     {
         tmp->next=top;
         top=tmp;
     }
}


void scan (stek *st) // zagolovok spiska
{
stek *p = new stek;
for (p = st; !p; p=p->next)
{
  printf ("%d ", *p);
  printf ("\n");
}
}*/				 
		   
 	 	   
			 
			 
		

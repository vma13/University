#include <iostream>
using namespace std;

typedef struct _s {
    struct _s *next;
    char x;
    unsigned int info;
    } stack;

typedef struct _d{
    char simb;
    int zn;
}dop;
dop mas[10];

char v[255];
stack *head;

    
void insert(char x)
{  stack *now;
    now=(stack *) malloc (sizeof(stack));
    now->x=x;
    now->info=0;
    now->next=head;
    head=now;
}
void insert2(int x)
{  stack *now;
    now=(stack *) malloc (sizeof(stack));
    now->x=0;
    now->info=x;
    now->next=head;
    head=now;

}

void del(){
if(head){
 stack *old=head;
 head=head->next;
 free(old);
}
else
 cout << "Error: Stack is empty!";
}

int main(){
  cout << insert(5);
  cout << insert2(10);
  return 0;
}
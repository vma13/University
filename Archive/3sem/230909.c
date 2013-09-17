#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int
 /* typedef struct Node{
   int value;
   struct Node *next;
  }Node;
  Node n1,n2,n3,*head;
  n1.value=1; n1.next=&n2;
  n2.value=3; n2.next=&n3;
  n3.value=7; n3.next=NULL;
  head=&n1
  
  Node *p;
  for(p=head; p!=NULL; p=p->next)
    printf("value=%d\n", p->value);
}*/
  
  
  
  
  /* typedef struct{
      int x,y;
    } R2Point;
   R2Point*p=(R2Point *)malloc(sizeof(R2Point)); 
      printf("p->x = ");scanf("%d", &p->x);
      printf("p->y = ");scanf("%d", &p->y);  
      p->x+=5;
      p->y-=10;
      printf("p1=(%d;%d)\n", p->x, p->y);
    free(p);
    return 0;
}*/

  

/*struct R2Point{
     int x,y;
  };
  int main(void) {
    typedef struct{
      int x,y;
    } R2Point;
    R2Point p1; 
      printf("p1.x->");scanf("%d", &p1.x);
      printf("p2.y->");scanf("%d", &p1.y);  
      p1.x+=5;
      p1.y-=10;
      printf("p1=(%d;%d)\n", p1.x, p1.y);
    return 0;
  }*/


/* int *a=(int *)malloc(5*sizeof(int));
	int i;
  
	for(i=0;i<5;i++){
		printf("a[%d]-> \n",i);scanf("%d", &a[i]);	
	}
	int *ai;
	for(ai=a,i=0;i<5;ai++,i++)
		printf("ai=%p;i=%d\n",ai,i);
*/



/* char *str1 = "Hello!";
  char *str2 = (char *) malloc(30);
  str2[0]='1';str2[1]='2';str2[2]='\0';
  strcat(str2,str1);
    printf("%s\n",str2);
}*/
 
 
 
 /* printf("%d\n",strlen(str2))
  unsigned(strlen(const char *str)){
   unsigned i;
   for (i=0,str[i]!=0;i++)
     return i
  }
   int i;
 char c;
for (i=0; str[i]!=0; i++)
  printf("%d\n",strlen(str2));
  printf("str1[%d]=%d:%c\n",i,str1[i],str1[i]);
}*/

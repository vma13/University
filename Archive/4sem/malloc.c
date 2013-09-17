#include <stdio.h>
#define BUF_SIZE (1024*1024+sizeof (struct block)*2)  
 typedef struct block{ 
  long size;
  struct block * next;
  } block;
  
  char buf[BUF_SIZE];                        

  void * mymalloc(long size){                
  static int first = 1;                          
  block *p,*tmp;
    if (first){                                   
      first=0;
      p=(block*)buf;
      p->size = 0;
      p->next=p+1;
      p=p+1;
      p->size=BUF_SIZE-sizeof(block)*2;
      p->next=NULL;        
      }
  if (size<=0) {return NULL;}              
  size=(size+sizeof(block)-1)&~(sizeof(block)-1);   
  for (p=(block*)buf,tmp=NULL; p!=NULL && p->size < size;tmp=p,p=p->next);        
  if (p==NULL){return NULL;}
  
  if (p->size > size){                                         
    p->size-=size+sizeof(block);
    p=(block*)((char*)p+p->size+sizeof(block));
    p->size=size;
    p->next=NULL;
    }else{tmp->next=p->next;}
    return ((char *)p + sizeof(block));               

  }
  
 void my_free(void* ptr){
  block *p;
  block *prv;
  block *nxt;
    nxt=(block*)buf;
    p = (block *)((char *)ptr - sizeof(p->size));
    for (prv=nxt;nxt!=NULL && p>nxt ;prv=nxt,nxt=nxt->next); 
    p->next=nxt; 
    prv->next=p; 
    if (((char*)p + p->size + sizeof(prv->size))==(char *)nxt){
      p->size+=nxt->size + sizeof(p->size); 
      p->next=nxt->next; 
    }
    if (((char*)prv + sizeof(prv->size) + prv->size)==(char *)p){
      prv->next=p->next;
      prv->size+=p->size+sizeof(p->size);
    }
}



int main() {
  return 0;
}

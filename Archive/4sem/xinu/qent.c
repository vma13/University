#define NQENT (NPROC* 2*NSEM + 4) // nsem - колличество семафоров в системе

struct qent{
  int gkey;
  int gnext;
  int gprev;
};

struct qent q[NQENT];

#define isempty(head)  (q[(head)].qnext > NPROC-1) 
#define noempty(head)  (q[(head)].qnext <= NPROC-1)
#define firstkey(head) (q[q[(head)].qnex].qkey)
#define lastkey(tail)  (q[q[(tail)].qprev].qkey)
#define firstid(head)  (q[(head)].qnext)

#define OK (1)
#define EMPTY (-1)
#define SYSERR (-1)

int enqueue(int item, int tail){
  struct qent* i;
  struct qent* t;
  i  = &q[item];
  t = &q[tail];
  i->qnext = tail;
  i->qprev = t->qprev;
  q[t->qprev].qnext = item; 
  t->qprev = i;
  return item;
}

int dequeue(int item){
  struct qent* i;
  i = &q[item];
  q[i->qprev].qnext = i->next;
  q[i->next].qprev = i->qprev;
  return item;
}

int insert_priority(int item, int head, int key){
  struct qent* h;
  h = &q[head];
  for(;h->qkey<key;h = &q[h->qnext])
  for(;q[head].qkey<qkey;head = q[head].qnext);
  enqueue(item,head);
  q[item].qkey =key;
  return OK;
}

int getfirst(int head){
  if(isempty(head)){
    return EMPTY;
    else
      return dequeue(q[head].qnext);
  }
}

int getlast(int tail){
  if(q[tail].qprev <=  NPROC-1)
    return dequeue(q[tail].qprev);
  else
    return EMPTY;
}

int newqueue(){ //инициализация цикла от NPROC до конца массива
}

#define PRCURR   1    //текущее
#define PRREADY  2    //готовое
#define PRFREE   3    //если состояния нет, эл-т таблицы свободен
#define PRRECV   4    //в данный момент ожидает собщения к себе
#define PRSLEEP  5    //вызван стандартный вызов sleep, по таймеру выводится
#define PRSUSP   6    //отложенный(приостановленый) - не активное(4-е) состояние переводиться по ctrl+z
#define PRWAIT   7    //ожидает какого-либо семафора, находиться в очереди к данному семафору
#define PNREGS   ...  //хранит флаги, регистры в таблицt процессов, машинно-зависимая = кол-ву процессоров задействованых на данной маш-е
#define PNMLEN   ...  //max длина имени процесса
#define NULLPROC 0    //в unix'e => init, остается жив когда все процессы закончeны
#define isbadpid(pid)  ((pid) <= 0 || (pid) > NPROC-1) //если переданый идентификатор не корректен

typedef struct pentry{
  int pstate;         //состояние процесса
  int pprio;          //приоритет процесса
  int pregs[PNREGS];  //массив для сохранения регистров
  int psem;           //номер того семафора, который процесс ожидает, если он его ожидает
  int pmsg;           //сообщение, которое пришло к процессу, если вообще пришло
  int phasmsg;        //булевый флажок, истина если процесс имеет сообщение, или лож если процесс не имеет собщения
  int *pbase;         //адрес стэка процессов
  int pstklen;        //длинна стэка процессов 
  int plimit;         //минимальное расширение стэка
  char pname[PNMLEN]; //имя процесса
  int pargs;          //начальное количество аргументов переданых процессу
  int *paddr;         //адрес с которого начинается выполнение процесса (стартовая точка)
};
struct pentry proctab[NPROC];
int numproc;          //колличесвтво существующих процессов
int currpid;          //идентификатор текущего процесса
int rdyhead;          //индекс головы в очереди готовых процессов
itn rdytail;          //индекс хвоста в очереди готовых процессов

int resched(void){    //sheduler
  struct pentry *p;
  struct pentry *p2;
  if (p = &proctab([currpid])->pstate == PRCURR && p->prio > lastkey(rdytail))
      return OK;
  if (p->pstate == PRCURR){
    p->pstate = PRREADY;
    insert(currpid, rdyhead, p->pprio);
  }
  p2 = &proctab[(currpid = getlast(rdytail)];
  p2->pstate = PRCURR;
  ctxsw(p->progs,p2->progs);
 return OK:
}

ctxsw(int* old_regs, int* new_regs); //context switcher

  disable();
  enable();
  
  int ready(int pid, int resch){
    pentry *p;
    if(isbadpid(pid)){
      return SYSERR;
    }
    p = &proctab[pid];
    insert(pid, rdyhead, p->pprio);
    p->pstate -> PRREADY;
    if(resched){
      return resch;
    }
  }

  int suspend(int pid){ //могут быть вызваны пользовательским процессом
    int prio;
    pentry *p;
    disable();
    if(isbadpid(pid) || (p =  &proctab[pid])->pstate != PRCURR && p->pstate != PRREADY){
      enable();
      return SYSERR;
    }
    if(p->state == PRREADY){
      dequeue(pid);
      p->state = PRSUSP;
    }else{
      p->state = PRSUSP;
      resched();
    }
    prio = p->pprio;
    enable();
    return prio;
  }
      
  int resume(pid){
    int prio;
    pentry *p;
    disable();
    if(isbadpid(pid) || (p = &proctab[pid])->pstate != PRSUSP){
      enable;
      return SYSERR;
    }
    prio = p->pprio;
    ready(pid, 1);
    enable();
    return prio;
  }
  
  int kill(int pid){
    pentry *p;
    disable();
    if(isbadpid(pid) || (p = &proctab[pid]->pstate) == PRFREE){
        enable;
        return SYSERR;
      }
      numproc--;
      free(p->pbase);
      switch (p-pstate){
      case PRCURR :
        p->pstate = PRFREE;
        resched();
        break;
      case PRWAIT :
        semaph[p->psem].semcnt++;
      case PRSLEEP :
      case PRREADY :
        dequeue(pid);
      default :
        p->pstate = PRFREE;
      }
        enable();
        return OK;
}
  int getprio(int pid){
    pentry *p;
    int prio;
    diasble();
    if(isbadpid(pid) || (p = &proctab[pid])->pstate == PRFREE){
      enable();
      return SYSERR;
    }
    prio = p->prio;
    enable();
    return prio;
  }

  int getpid(){
    return curpid;
  }
    
  int chprio(int pid, int newprio){
    pentry *p;
    int prio;
    disable();
    if(isbadpid(pid) || (p = &proctab[pid])->pstate == PRFREE || newprio < 0){
      enable();
      return SYSERR;
    }
    p = p->prio;
    p->prio = newprio;
    enable();
    return prio;
  }

  struct sentry{
    int sstate;
    int semcnt; //отрицателен если ожидают семафоры; >= 0, если очередь пуста
    int sqhead;
    int sqtail;
  };
#define SFREE 0
#define SUSED 1
#define NSEM
struct sentry semaph[NSEM]
#define isbadsem(sem) ((sem) < 0 || sem >= NSEM)
    //P - xinu wait
    //v - signal number of semaph
  int wait(int sem){
  struct sentry *s;
  struct sentry *p;
  disable();
  if(isbadsem(sem) || (s = &semaph(sem))->sstate == SFREE){
     enable();
     return SYSERR;
  }
  if(--s->semcnt < 0){
    p = &proctab[currpid];
    p->pstate = PRWAIT;
    p->psem = sem;
    enqueue(currpid, s->sqtail);
    resched();
    enable();
    return OK;
  }
}
 int signal(int sem){
   struct sentry *s;
   disable();
   if(isbadsem(sem) || (s = &semaph(sem))->sstate == SFREE){
       enable();
       return SYSERR;
     }
   if(++s->semcnt < 0)
     ready(getfirst(s->sqhead), 1);
   enable();
   return OK;
 }

 int screate(int count){
   sentry *s;
   int i;
   disable();
   if(count < 0){
     enable();
     return SYSERR;
   }
   for  (i = 0; i < NSEM; i++){
    if (semaph[i].sstate == SFREE){
      break;
    }
  }
  if (i == NSEM){
    enable();
    return SYSERR;
  }
  s = &semaph[i];
  s->semcnt = count;
  s->sstate = SUSED;
  enable();
  return i;
 }

 int sdelete(int sem){
   sentry *s;
   int pid;
   disable();
   if(isbadsem(sem) || s = &semaph(sem)->sstate == SFREE){
     enable();
     return SYSERR;
   }
   s->sstate == SFREE;
   if(noempty(s->sqhead)){
     while(pid = getfirst(s->sstate) != SEMPTY){
       ready(pid, 0);
      };
   resched();
 }
 enable();
 return sem;
 }

 int send(int pid, int msg){
   pentry *p;
   disable();
   if(isbadpid(pid) || (p = &proctab[pid])->pstate == PRFREE || p->phasmsg){
       enable();
       return SYSERR;
     }
   p->hasmsg = 1;
   p->msg = msg;
   if(p->pstate == PRRECV){
     ready(pid,1);
   }
   enable();
 }

 int recieve(){
   pentry *p;
   int msg;
   disable();
   p = &proctab[currpid];
   if(p->phasmsg == 0){
     p->pstate = PRRECV;
     resched();
   }
   msg = p->pmsg;
   p->pstate = 0;
   enable();
   return msg;
 }


 

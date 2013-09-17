/*
  NPROC - количество процессов
  NSEM - количество семафоров
  Очередей много. Каждый элемент массива только в одной очереди. Головы и хвосты в массиве начиная с NPROC и ниже (процессы). Остельное головы и хвосты. Головы и хвосты лежат поочереди(голова, хвост). Всего NSEM + 2 очередей. Каждая очередь отсортирована по возрастанию ключа. -1, если нету (головы/хвоста) 
*/
#define NQUENT (NPROC + 2 * NSEM + 4)
typedef struct qent{
  int key;
  int qnext;
  int qprev;
}qent ;
struct qent q[NQUENT];
#define isempty(head) (q[(head)].qnext >= NPROC)
#define nonempty(head) (q[(head)].qnext < NPROC)
#define firstkey(head) (q[q[(head)].qnext].key)
#define lastkey(tail) (q[q[(tail)].qprev].key)
#define firstid(head) (q[(head)].qnext)
#define EMPTY (-1)
#define OK (1)
#define SYSERR (-1)

int enqueue (int item, int tail){
  qqent *i, *t;
  i = &(q[item]);
  t = &(q[tail]);
  i->qnext = tail;
  i->qprev = t->qprev;
  q[t->qprev].qnext = item;
  t->qprev = item;
}

int dequeue (int item){
  qent * p = &q[item];
  q[p->qprev].qnext = p->qnext;
  q[p->qnext].qprev = p->qprev;
  return item;
}

int insert (int proc, int head, int key){
  qent * a = &q[head];
  int i = head;
  while (q[i]->key < key){
    i = q[i].qnext;
  }
  enqueue(proc,i); 
  q[proc].key = key;
  return OK;
}

int getfirst (int  head){
  if (isempty(head)) return EMPTY;
  return dequeue(q[head].qnext);
}

int getlast (int  tail){
  if (q[tail].qprev >= NPROC) return EMPTY;
  return dequeue(q[tail].qprev);
}

int newqueue(void){
  /*инициализировать head и tail и возвращает индекс головы*/
}

#define NPROC 100500

#define PRCURR 1 //текущий процесс
#define PRFREE 2 //несуществующий процесс
#define PRREADY 3 //готовый процесс
#define PRRECV 4 //процесс принимающий сообщения
#define PRSLEEP 5 //спящий процесс
#define PRSUSP 6 //suspended отложенный процесс
#define PRWAIT 7 //ожидает семафора

#define PNREGS ... //коллиqество регистров в процессоре на данное
                   //время
#define PNMLEN ... // максимальное количество символов в имени
                   // процесса
#define NULPROC 0 //нулевой процесс(который остаётся жить, когда все
                  //закончены
#define isbadpid(pid) ((pid) <= 0 || (pid) >= NPROC)  //если
                                                      //переданный
                                                      //идентификатор
                                                      //не корректен

typedef struct pentry {
  int pstate; //состояние процесса
  int pprio; //приоритет процесса
  int pregs[PNREGS]; //массив сохранения регистров
  int psem; // номер семафора, который получает процесс, если ожидает
  int pmsg; // сообщение, которое получает процесс
  int phasmsg; // флаг, есть ли у данного процесса сообщение
  void *pbase; // указатель на стек процесса
  int pstklen; //длина стека
  int plimit; // минимальное расширение стека
  char pname[PNMLEN]; //имя процесса
  int pargs; // начальное количество аргументов процесса
  void *paddr; // адрес процесса в памяти(ОЗУ)
}pentry ;

typedef struct sentry {
  int sstate; //существ/несущ
  int semcnt; //счётчик
  int sqhead; //голова и хвост к очереди семафора
  int sqtail;
}sentry;
sentry semaph[NSEM];

#define SFREE 1 //существует семафор или нет
#define SUSED 2
#define isbadsem(sem) ((sem) < 0 || (sem) >= NSEM)
pentry proctab[NPROC];
// индекс в массиве proctab  и в q идентичны и являются pid
int currpid; // id текущего процесса
int numproc; //количество существующих в данный момент процессов
int rdyhead;
int rdytail;

/*
Все готовые процессы в очереди.
*/

int resched(void){
  pentry *nprt, *optr;
  optr = &proctab[currpid];
  if (optr->pstate == PRCURR && optr->pprio > lastkey(rdytail())){
    return OK;
  }
  if (optr->pstate == PRCURR){
    optr->state = PRREADY;
    insert(currpid, rdyhead, optr->pprio);
  }
  nptr = &proctab[(currpid = getlast(rdytail))];
  nptr->pstate = PRCURR;
  ctxsw(optr->progs, nptr->progs);
  return OK;
}

int ready (int pid, int resch){
  pentry *p;
  if (isbadpid(pid))
    return SYSERR;
  p = &proctab[pid];
  p->pstate = PRREADY;
  insert(pid, rdyhead, p->pprio);
  if (resch)
    resched();
  return OK;
}

/*запрещает/разрешает прерывания*/
#define disable();
#define enable();
/*ниже системные вызовы*/
int suspend(int pid){
  pentry *p;
  int prio;
  disable();
  if (isbadpid(pid) || (p = &proctab[pid])->pstate != PRCURR && p->state != PRREADY){
    enable();
    return SYSERR;
  }
  if (p->pstate == PRREADY){
    dequeue(pid);
    p->pstate = PRSUSP;
  }else{
    p->pstate = PRSUSP;
    resched();
  }
  prio = p->pprio;
  enable();
  return prio;
}

int resume(int pid){
  pentry *p;
  int prio;
  disable();
  if (isbadpid(pid) || (p = &proctab[pid])->pstate != PRSYS){
    enable();
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
  if (isbadpid(pid) || (p = &proctab[pid])->pstate == PRFREE){
    enable();
    return SYSERR;
  }
  numproc--;
  my_free(p->pbase);
  switch (p->state){
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

int getprio (int pid){
  pentry *p;
  int prio;
  disable();
  if (isbadpid(pid) || (p = &proctab[pid])->pstate == PRFREE) {
    enable();
    return SYSERR;
  }
  prio = p->pprio;
  enable();
  return prio;
}

int getpid(void){
  return currpid;
}

int chprio(int pid, int newprio){
  pentry *p;
  int prio;
  disable();
  if (isbadpid(pid) || (p = &proctab[pid])->pstate == PRFREE) {
    enable();
    return SYSERR;
  }
  prio = p->pprio;
  p->pprio = newprio;
  enable();
  return prio;
}
// if semcnt > 0, очередь данного семафора пуста, if semcnt < 0 == -n
// (n -- кол-во процессов ожидающих семафора
int screate(int count){
  sentry * s;
  int i;
  disable();
  if (count < 0){
    enable();
    return SYSERR;
  }
  for (i = 0; i < NSEM; i++){
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
  if (isbadsem(sem) || (s = &semaph[sem]->sstate) == SFREE){
    enable();
    return SYSERR;
  }
  s->sstate = SUSED;
  if (nonempty(s->sqhead)){
    while ((pid = getfirst(s->sqhead)) != EMPTY){
      ready(pid,0);
    };
    reshed();
  }
  enable();
  return sem;
}

int send(int pid, int msg){
  pentry *p;
  disable();
  if (isbadpid(pid) || (p = &proctab[pid])->phasmsg != 0 ){
    enable();
    return SYSERR;
  }
  p->hasmsg = 1;
  p->msg = msg;
  if (p->pstate == PRRECV){
    ready(pid,1);
  }
  enable();
  return OK;
}

int recieve(){
  pentry *p;
  int msg;
  disable();
  p = &proctab[currpid];
  if (p->phasmsg == 0){
    p->pstate = PRRECV;
    resched();
  }
  msg = p->pmsg;
  p->phasmsg = 0;
  enable();
  return msg;
}

int wait (int sem) {
  struct sentry *ps;
  struct pentry *pp;
  disable();
  if (isbadsem(sem) || (ps = &semaph[sem])->sstate == SFREE) {
    enable();
    return SYSERR;
  }
  if (--ps->semcnt < 0) {
    pp = &proctab[currpid];
    pp->pstate = PRWAIT;
    pp->psem = sem;
    enqueue(currpid, ps->sqtail);
    resched();
  }
  enable();
  return OK;
}

int signal(int sem) {
  struct sentry *ps;
  disable();
  if (isbadsem(sem) || (ps = &semaph[sem])->sstate == SFREE) {
    enable();
    return SYSERR;
  }
  if (ps->semcnt++ < 0)
    ready(getfirst(ps->sqhead), 1);
  enable();
  return OK;
}







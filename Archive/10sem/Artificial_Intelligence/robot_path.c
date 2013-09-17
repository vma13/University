#include <stdio.h> 
#include <malloc.h> 

//Поле 10х10 для движения робота
#define SIZE 10
int field[SIZE][SIZE]; 
int start_i, start_j; 
int finish_i, finish_j;
// Ячейки поля
#define FREE 0      // свободная ячейка
#define OBSTACLE 1  // препятствие
#define USED 2      // ячейка через которую робот уже проходил (назад ходить нельзя)
// Возможные действия
#define NOTHING 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define DOWN_RIGHT 5
#define UP_LEFT 6
#define UP_RIGHT 7
#define DOWN_LEFT 8

// Узел
typedef struct node{
	int state[2];
	struct node *parent;
	int depth; 
	int action;
}node;
// Массив
typedef struct array{
	node **arr;
	int size; 
}array;

// Очередь из узлов
typedef struct queue{
	void* uzel;
	struct queue *next;
	struct queue *prev;
} queue;

// Создание очереди из узлов
queue* QueueCreate(void){
	queue *header = (queue*)malloc(sizeof(queue)); 
	header->next = header;
	header->prev = header;
	header->uzel = NULL; 
	return header;
}
// Проверка очереди на пустоту
int QueueIsEmpty(queue *header){
	return (header->next == header);
}
// Добавление узла в очередь
void QueueAdd(queue* header, void* uzel){
	queue *n = (queue*)malloc(sizeof(queue));
        n->next = header;
	n->prev = header->prev;
	n->uzel = uzel; 
	header->prev->next = n; 
	header->prev = n; 
}
// Перебор узлов очереди
void* QueueGet(queue* header){
	if (QueueIsEmpty(header)){
	 return NULL; 
	}
	void *uzel = header->next->uzel; 
	header->next = header->next->next;
	free(header->next->prev); 
	header->next->prev = header;
	return uzel;
}
// Проверка на попадание координат узла в поле field (10x10)
char Include_field(int i, int j){ 
	return (i >= 0 && i < SIZE && j >= 0 && j < SIZE);
}
// Создание нового узла
node* NodeCreate(int i,int j, node *p, int depth, int action){
	node *successor = (node*)malloc(sizeof(node)); 
	successor->state[0] = i;
	successor->state[1] = j; 
	successor->parent = p; 
	successor->depth = depth; 
	successor->action = action; 
	return successor; 
}
// Печать узла
void NodePrint(node *n){
 printf("Узел:\n");
 printf("  Координаты узла = (%d, %d)\n",n->state[0],n->state[1]);
  if(n->parent==NULL)printf("  Родитель отсутствует\n");
  printf("  Глубина         = %d\n",n->depth);
  if(n->action==NOTHING)printf("  Действие        = 'Ничего'\n");
  if(n->action==LEFT)printf("  Действие        = 'Влево'\n");
  if(n->action==RIGHT)printf("  Действие        = 'Вправо'\n");
  if(n->action==UP)printf("  Действие        = 'Вверх'\n");
  if(n->action==DOWN)printf("  Действие        = 'Вниз'\n");
  if(n->action==DOWN_RIGHT)printf("  Действие        = 'Вниз направо'\n");
  if(n->action==UP_LEFT)printf("  Действие        = 'Вверх налево'\n");
  if(n->action==UP_RIGHT)printf("  Действие        = 'Вверх направо'\n");
  if(n->action==DOWN_LEFT)printf("  Действие        = 'Вниз налево'\n");
}

// Функция Expand возращает множество узлов successor
array Expand(node *n){ 
  array successor; 
  successor.size = 0;
  int i = 0;
  // Количество возможных прямолинейных шагов 
  if(Include_field(n->state[0]+1, n->state[1]) && n->action != UP) // вниз
    if(field[n->state[0]+1][n->state[1]] != OBSTACLE)successor.size++;
  if(Include_field(n->state[0]-1, n->state[1]) && n->action != DOWN) // верх
    if(field[n->state[0]-1][n->state[1]] != OBSTACLE)successor.size++;
  if(Include_field(n->state[0], n->state[1]+1) && n->action != LEFT) // вправо
    if(field[n->state[0]][n->state[1]+1] != OBSTACLE)successor.size++;
  if(Include_field(n->state[0], n->state[1]-1) && n->action != RIGHT) // влево
    if(field[n->state[0]][n->state[1]-1] != OBSTACLE)successor.size++;
  // Количество возможных шагов по диагонали
 /* if(Include_field(n->state[0]+1, n->state[1]+1) && n->action != UP && n->action != LEFT) // вниз вправо
    if(field[n->state[0]+1][n->state[1]+1] != OBSTACLE)successor.size++;
  if(Include_field(n->state[0]-1, n->state[1]-1) && n->action != DOWN && n->action != RIGHT) // вверх влево
    if(field[n->state[0]-1][n->state[1]-1] != OBSTACLE)successor.size++;
  if(Include_field(n->state[0]-1, n->state[1]+1) && n->action != DOWN && n->action != LEFT)  // вверх вправо
    if(field[n->state[0]-1][n->state[1]+1] != OBSTACLE)successor.size++;
  if(Include_field(n->state[0]+1, n->state[1]-1) && n->action != UP && n->action != RIGHT) // вниз влево
    if(field[n->state[0]+1][n->state[1]-1] != OBSTACLE)successor.size++;
*/
  successor.arr = (node**)malloc(sizeof(node*)*successor.size); // временный массив для периферии
  
  // Добавляем возможные действия во временный массив 
  if(Include_field(n->state[0]-1, n->state[1]) && n->action != DOWN)
  if(field[n->state[0]-1][n->state[1]] != OBSTACLE){
    successor.arr[i] = NodeCreate(n->state[0]-1, n->state[1], n, n->depth+1, UP);
    i++;
  }
  if(Include_field(n->state[0]+1, n->state[1]) && n->action != UP)
  if(field[n->state[0]+1][n->state[1]] != OBSTACLE){
    successor.arr[i] = NodeCreate(n->state[0]+1, n->state[1], n, n->depth+1, DOWN);
    i++;
  }
  if(Include_field(n->state[0], n->state[1]-1) && n->action != RIGHT)
  if(field[n->state[0]][n->state[1]-1] != OBSTACLE){
    successor.arr[i] = NodeCreate(n->state[0], n->state[1]-1, n, n->depth+1, LEFT);
    i++;
  }
  if(Include_field(n->state[0], n->state[1]+1) && n->action != LEFT)
  if(field[n->state[0]][n->state[1]+1] != OBSTACLE){
    successor.arr[i] = NodeCreate(n->state[0], n->state[1]+1, n, n->depth+1, RIGHT);
    i++;
  }
/*
  if(Include_field(n->state[0]+1, n->state[1]+1) && n->action != UP && n->action != LEFT )
  if(field[n->state[0]+1][n->state[1]+1] != OBSTACLE){
    successor.arr[i] = NodeCreate(n->state[0]+1, n->state[1]+1, n, n->depth+1, DOWN_RIGHT);
    i++;
  }
  if(Include_field(n->state[0]-1, n->state[1]-1) && n->action != RIGHT && n->action != DOWN )
  if(field[n->state[0]-1][n->state[1]-1] != OBSTACLE){
    successor.arr[i] = NodeCreate(n->state[0]-1, n->state[1]-1, n, n->depth+1, UP_LEFT);
    i++;
  }
  if(Include_field(n->state[0]-1, n->state[1]+1) && n->action != LEFT && n->action != DOWN )
  if(field[n->state[0]-1][n->state[1]+1] != OBSTACLE){
    successor.arr[i] = NodeCreate(n->state[0]-1, n->state[1]+1, n, n->depth+1, UP_RIGHT);
    i++;
  }
  if(Include_field(n->state[0]+1, n->state[1]-1) && n->action != RIGHT && n->action != UP )
  if(field[n->state[0]+1][n->state[1]-1] != OBSTACLE){
    successor.arr[i] = NodeCreate(n->state[0]+1, n->state[1]-1, n, n->depth+1, DOWN_LEFT);
    i++; 
  }*/
  return successor;
}
// Проверка, пришли ли мы к цели
char NodeIsFinish(node *n){
	return (n->state[0] == finish_i && n->state[1] == finish_j);
}
// Загружаем файл с полем 
int FieldOpen(){
 int i,j;
 char tmp[100];
 FILE *file = fopen("Field.txt","r+");
 for(i = 0; i < 10; i++){ 
  fscanf(file,"%s",&tmp);
   for(j = 0; j < 10; j++){
    switch(tmp[j]){ 
      case 'S': 
        field[i][j] = FREE;
        start_i = i;
        start_j = j;
        break;
      case 'F': 
        field[i][j] = FREE;
        finish_i = i;
        finish_j = j;
      break; 
      case 'x': 
        field[i][j] = OBSTACLE;
      break;
      default:
        field[i][j] = FREE;
      break;
    }
   }
 }
 fclose(file); 
 return 0;
}
// Поиск в ширину (FIFO)
int TreeSearch(){
 int i,j;
 node *n = NodeCreate(start_i,start_j,NULL,0,NOTHING); 
 array arr; 
 queue *h = QueueCreate();
 QueueAdd(h,n); 
 while(!QueueIsEmpty(h)){
   n = QueueGet(h); 
     if(NodeIsFinish(n)){ 
	while(n->parent != NULL){ 
	  NodePrint(n); 
	  field[n->state[0]][n->state[1]] = USED;
       	  n = n->parent;
	}
	field[n->state[0]][n->state[1]] = USED;
	printf("\nКарта пути:\n");
	printf("\"X\" - Препятствие\n");
	printf("\".\" - Свободная ячейка\n");
        printf("\"*\" - Путь робота\n\n");
	for(i = 0; i<SIZE; i++){ 
	  for(j = 0; j<SIZE; j++){
	    if(field[i][j] == FREE)printf(".");
	    if(field[i][j] == OBSTACLE)printf("X");
	    if(field[i][j] == USED)printf("*");
	  }
	  printf("\n");
	}
	free(h);
	return 0;
     }
     //если решение еще не нашлось, то заново записываем переферию
     arr = Expand(n);
     for(i = 0; i < arr.size; i++){
       QueueAdd(h, arr.arr[i]);
     }
 } 
 printf("Can't find solution\n");
 free(h);
return 0;
}

// Функция main()
int main(){
 FieldOpen();
 TreeSearch();
}

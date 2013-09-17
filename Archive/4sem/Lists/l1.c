#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct l1 {
  struct l1* next;
  int key;
} l1;

l1* l1_head = NULL;

l1* l1_insert( int key ){
  l1* p;
  l1** q;

  for( q = &l1_head; *q != NULL && (*q)->key < key; q = &( (*q)->next ) );
  if( ( p = (l1*)malloc( sizeof( l1 ) ) ) == NULL ){
    fprintf( stderr, "Not enough memory\n" );
    exit( 1 );
  }
  p->key = key; p->next = *q;
  return *q = p;
}

void l1_remove( int key ){
  l1* p;
  l1** q;

  printf( "Removing first item with key (%d)...\n", key );
  for( q = &l1_head; *q != NULL && (*q)->key != key; q = &( (*q)->next ) );
  if( *q != NULL ){ p = *q; *q = (*q)->next; free( p ); }
}

void l1_print( void ){
  l1* p;
  
  printf( "l1_list contents:\n" );
  for( p = l1_head; p != NULL; p = p->next )
    printf( "p = %p, p->key = %d, p->next = %p\n", p, p->key, p->next );
  printf( "#####################\n" );
}

int main( void ){
  l1_print();

  l1_insert( 10 ); l1_print();
  l1_insert( 9 );  l1_print();
  l1_insert( 11 ); l1_print();
  l1_insert( 12 ); l1_print();
  l1_insert( 10 ); l1_print();
  l1_insert( 8 );  l1_print();

  l1_remove( 10 ); l1_print();
  l1_remove( 8 );  l1_print();
  l1_remove( 9 );  l1_print();
  l1_remove( 10 ); l1_print();
  l1_remove( 11 ); l1_print();
  l1_remove( 12 ); l1_print();

  return 0;
}  

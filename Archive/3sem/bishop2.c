#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void char2int ( char *, int);
void sub ( char *, int , int );
void mul ( char *, int , int );
void print ( char *, int );
void transfer(char *, int);
void clear(char *);

int main()
{
    int len;
    char a[103];   
    while( scanf("%s", a)!=-1)
    {
        len = strlen ( a);
        if ( len == 1)
        {
            if ( a[0] == '0') /*special case of 0 */
                printf("0\n");
            else if ( a[0] == '1')  /*special case of 1 */
                    printf("1\n");
                 else
                 {  /*rest single digit numbers take care here*/
                     char2int( a, len);   
                    transfer( a, len);
                    mul ( a, len, 2 );
                    sub ( a, len, 2 );
                    print( a , len);   
                 }
        }
        else
        {
            char2int( a, len);   
            transfer( a, len);   /*transfers the numbers from one end of array to the other end */
            mul ( a, len, 2 );
            sub ( a, len, 2 ); 
            print( a , len);
        }       
        clear(a);
    }
    return 0;   
}

void clear( char *a)
{
    int i;
    for ( i = 102; i >= 0;i--)
        a[i] = 0;
}

void sub ( char *a, int len, int b)
{
     int i, k;
     for( i = 102; i>=0; i--)
     {
          k = a[i] - b;
          if( k < 0)
          {
              a[i-1] = a[i-1] - 1;
              a[i] = 10 + a[i] - b;
          }
          else
              a[i]=k;
             
            b = 0;
     }
}

void char2int ( char *a, int alen)
{
    int i;
    for( i=0; i < alen; i++)
    {
        *(a+i) = *(a+i) - 48;
    }
}

void mul ( char *a, int len, int num)
{
    int j, borrow = 0;
    for ( j = 102; j >0; j--)
    {
        borrow = a[j] * num + borrow;
        a[j] = borrow % 10;
        borrow = borrow / 10;
    } 
}

void print( char *a, int len)
{
     int i=0;
     while ( a[i] == 0 )
     {
          i++;
     }
     for( ; i <= 102; i++)
     {
          printf("%d",*(a+i));
     } 
     printf("\n");   
}

void transfer( char *a, int alen)
{
    int i;
    for( i=0;i<=alen;i++)
    {
        a[102-i]=a[alen-1-i];
    }
    for( i=102-alen-1;i>=0;i--)
    {
        a[i]=0;
    }
}

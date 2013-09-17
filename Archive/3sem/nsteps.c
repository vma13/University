#include<stdio.h>
int main(void)
{
  int cases,i,x,y,j;
  int value[30000];
 
  scanf("%d",&cases);
 
  for(i=0;i<cases;i++)
  {
    scanf("%d %d",&x,&y);
   
    /* all the following conditions result in "No Number" */
    /* 1.when y > x
       2.when x is odd & y is even or vice versa
       3.when x>2 and y=0
    */
    if(y>x || (x%2!=0 && y%2==0) || (x%2==0 && y%2!=0 ) || (x>2 && y==0))
      value[i]=-1;                           /* a flag to indicate "No Number"       */
     
    else
    {
      if(x==y && ((x%2)==0))          /* when both same and even */
       value[i]=2*x; 
     
      else if(x==y && ((x%2)!=0))     /* when both same and odd */
        value[i]=(2*x)-1;
       
      else if(x%2==0 && y%2==0)       /* when both even and different */
        value[i]=x+y;
      else if(x%2!=0 && y%2!=0)       /* when both odd  and different */
        value[i]=x+y-1;
    }
  }
 
  /* output begins */
 
  printf("\n");
  for(j=0;j<i;j++)
  {
    if(value[j]==-1)
     printf("No Number\n");
    else
     printf("%d\n",value[j]);
  }
  return 0;
}
/*There are a lot more cases where there is no number.. how about (10001,1)*/
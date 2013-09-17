#include <stdio.h>

int Z(int n) {
	int result = 0,i;
	for (i = 5; i <= n; i *= 5)
		result += n/i;
	return result;
}


int main()
{
  int numStr;
  int i;
  int j,k;
  scanf("%d", &numStr);
  int c[numStr];
  for( i=0; i<numStr; i++)
  {
      scanf("\n%d", &j);
      c[i] = j;
  }
  for( k=0; k<numStr; k++ )
      printf("%d\n" , Z(c[k]) );
     getch();
    return 0; 
}



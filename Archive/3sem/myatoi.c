#include <stlib.h>
#include <stdio.h>

int new_atoi(const char* string)
{
 if(!string) return 0;
 int result = 0;

 //пропускаем пробельные символы
 while(*string == ' ' || *string == '\t' ) string++;

 // получаем знак числа
 bool bNegativeSign = (*string == '-');

 if(bNegativeSign || *string=='+') string++;

 while(*string) {
   if( (*string < '0' || *string> '9') ) break;
   result = result * 10 + (*string - '0');
   string++;
 }
return ( bNegativeSign ? -result : result );
}
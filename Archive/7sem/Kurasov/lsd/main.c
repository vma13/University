#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

char line1[16] = "Hello World!    ";

int main(void) {
  unsigned int i, j;
  lcdinit();
	
  while(1){
	 for(i = 0; i < 16; i++) {
	  lcdprintc(line1[i]);
	  for(j = 0; j < 50; j++)
	    _delay_ms(30);
	  
    }
		lcdclear();
		for(j = 0; j < 30; j++)
		  _delay_ms(10);
  }
		
  return 0;
}

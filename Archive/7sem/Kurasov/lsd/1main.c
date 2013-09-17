#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.c"

int main(void) {
  unsigned char i;
  lcdinit();
  //lcdprints(line);
  //lcdsecondline();
  //lcdprints(line);
    for(i = 0x21; i < 0x31; i++)
      lcdprintc(i);
    while(1);
    
    //lcdsecondline();
    //lcdprints(line);
    //lcdclear();
    //_delay_ms(20);
  return 0;
}

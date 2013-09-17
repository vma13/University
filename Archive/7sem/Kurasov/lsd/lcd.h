//My LCD Library

#define RS 0
#define E 1


void cbi(unsigned char bit) {
  PORTB &= ~(1 << bit);
}

void sbi(unsigned char bit) {
  PORTB |= (1 << bit);
}

void lcdcmd(unsigned char cmd) {
  cbi(RS);
  PORTD = cmd & 0xF0;
  sbi(E);
  _delay_us(2);
  cbi(E);
  _delay_us(2);
  sbi(E);
  _delay_us(2);
  PORTD = cmd << 4;
  cbi(E);
  PORTD = 0xFF;
  _delay_ms(3);
}

void lcddata(unsigned char data) {
  sbi(RS);
  PORTD = data & 0xF0;
  sbi(E);
  _delay_us(2);
  cbi(E);
  _delay_us(2);
  sbi(E);
  _delay_us(2);
  PORTD = data << 4;
  cbi(E);
  cbi(RS);
  PORTD = 0xFF;
  _delay_ms(1);
}

void lcdclear(void) {
  lcdcmd(0x01);
}

void lcdentrymode(unsigned char cmd) {
  lcdcmd(cmd);
}

void lcddisplayon(void) {
  lcdcmd(0x0C);
}

void lcddisplayoff(void) {
  lcdcmd(0x08);
}

void lcdhome(void){
  lcdcmd(0x02);
}
void lcdsecondline(void){
  lcdcmd(0xBD);
}

void lcdshiftleft(void){
  lcdcmd(0x10);
}

void lcdshiftright(void){
  lcdcmd(0x14);
}

void lcdinit(void) {
  PORTB = 0xFF;
  DDRB = 0xFF;
  PORTD = 0xF0;
  DDRD = 0xF0;
  
  _delay_ms(60);
  
  lcdcmd(0x20);
  lcdcmd(0x28);

  lcddisplayoff();

  lcddisplayon();

  lcdclear();
  
  lcdentrymode(0x06);
  
}

void lcdprints(char *s){
  while(*s) {
    lcddata(*s);
    s++;
  }
}

void lcdprintc(unsigned char c) {
  lcddata(c);
}

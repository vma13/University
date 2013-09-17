//My LCD Library

#define RS 0
#define E 1
#define RW 2


void cbi(unsigned char bit) {
  PORTB &= ~(1 << bit);
}

void sbi(unsigned char bit) {
  PORTB |= (1 << bit);
}

void lcdcmd(unsigned char cmd) {
  cbi(RS); //Command
  sbi(E);
  PORTD = cmd;
  _delay_us(2);
  cbi(E);
  _delay_ms(1);
}

void lcddata(unsigned char data) {
  cli();
  sbi(RS); //Data
  _delay_us(1);
  sbi(E);
  PORTD = data;
  _delay_us(2);
  cbi(E);
  _delay_us(1);
  cbi(RS);
  _delay_us(50);
}

void lcdclear(void) {
  lcdcmd(0x01);
  _delay_ms(5);
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
  _delay_ms(5);
}
void lcdsecondline(void){
  lcdcmd(0xC0);
}

void lcdshiftleft(void){
  lcdcmd(0x10);
}

void lcdshiftright(void){
  lcdcmd(0x14);
}

void lcdinit(void) {
  unsigned char i = 100;
  while(i > 0) {
    _delay_ms(10);
    i--;
  }
  PORTB = 0x00;
  DDRB = 0xFF;
  PORTD = 0x00;
  DDRD = 0xFF;
  
  lcdcmd(0x30);
  _delay_ms(5);
  lcdcmd(0x30);
  _delay_ms(5);
  lcdcmd(0x30);
  _delay_ms(5);
  lcdcmd(0x38);
  _delay_ms(5);
  //lcdcmd(0x30);
  //_delay_us(150);
  //lcdcmd(0x30);
  //lcdcmd(0x38);
  //_delay_ms(50);

  lcdclear();
  lcdclear();
  lcdclear();
  
  lcdentrymode(0x06);
  lcdentrymode(0x06);
  lcdentrymode(0x06);

  lcddisplayon();
  _delay_ms(1);
  lcddisplayon();
  _delay_ms(1);
  lcddisplayon();
  _delay_ms(1);
}

void lcdprints(char *s){
  unsigned int i;
  i = 0;
  while(s[i] != '\0') {
    lcddata(s[i]);
    i++;
  }
}

void lcdprintc(unsigned char c) {
  lcddata(c);
}

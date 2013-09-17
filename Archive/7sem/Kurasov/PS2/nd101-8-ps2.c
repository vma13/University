#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/wdt.h>

#define sce0 	PORTC &= 0XFd //Chip Select
#define rst0 	PORTC &= 0XFb //Reset
#define dc0 	PORTC &= 0XEF //1 to write data,0 to write instructions
#define sdin0 	PORTB &= 0XF7 //Data
#define sclk0 	PORTB &= 0XDF //clock

#define sce1 	PORTC |= 0X02 //Chip Select
#define rst1 	PORTC |= 0X04 //Reset
#define dc1 	PORTC |= 0X10 //1 to write data,0 to write instructions
#define sdin1 	PORTB |= 0X08 //Data
#define sclk1 	PORTB |= 0X20 //clock

#define hc138dis 	PORTB &= 0XEF //g = 0
#define hc138en		PORTB |= 0X10 //g = 1

#define  Key_Data (PIND&0X10)
#define  Key_CLK (PIND&0X08) 

typedef union
{
  unsigned char  Byte;
  struct  
  {
    unsigned char  bit0 		:1;
    unsigned char  bit1 		:1;
    unsigned char  bit2 		:1;
    unsigned char  bit3 		:1;
    unsigned char  bit4 		:1;
    unsigned char  bit5 		:1;
    unsigned char  bit6 		:1;
    unsigned char  bit7 		:1;
  } Bits;
} BitField;
volatile BitField _FLAG; 
//#define FLAG         _FLAG.Byte
#define bf       _FLAG.Bits.bit0
#define disbit   _FLAG.Bits.bit1
#define clrbit   _FLAG.Bits.bit2
unsigned char IntNum = 0; //count the number of interrupts
unsigned char KeyV; //key
unsigned char DisNum = 0; //display with the pointer
unsigned char Key_UP = 0, Shift = 0; //Key_UP is key to release the identity, Shift is the Shift key pressed logo
unsigned char keybuf;
unsigned char disbuf;

const prog_char UnShifted[] = {
  0x1C, 65,//'a',
  0x32, 66,//'b',
  0x21, 67,//'c',
  0x23, 68,//'d',
  0x24, 69,//'e',
  0x2B, 70,//'f',
  0x34, 71,//'g',
  0x33, 72,//'h',
  0x43, 73,//'i',
  0x3B, 74,//'j',10
  0x42, 75,//'k',
  0x4B, 76,//'l',
  0x3A, 77,//'m',
  0x31, 78,//'n',
  0x44, 79,//'o',
  0x4D, 80,//'p',
  0x15, 81,//'q',
  0x2D, 82,//'r',
  0x1B, 83,//'s',20
  0x2C, 84,//'t',
  0x3C, 85,//'u',
  0x2A, 86,//'v',
  0x1D, 87,//'w',
  0x22, 88,//'x',
  0x35, 89,//'y',
  0x1A, 90,//'z',
  0x45, 16,//'0',
  0x16, 17,//'1',30
  0x1E, 18,//'2',
  0x26, 19,//'3',
  0x25, 20,//'4',
  0x2E, 21,//'5',
  0x36, 22,//'6',
  0x3D, 23,//'7',
  0x3E, 24,//'8',
  0x46, 25,//'9',
  0x70, 16,//'0',
  0x69, 17,//'1',40
  0x72, 18,//'2',
  0x7A, 19,//'3',
  0x6B, 20,//'4',
  0x73, 21,//'5',
  0x74, 22,//'6',
  0x6C, 23,//'7',
  0x75, 24,//'8',
  0x7D, 25,//'9',

  0x4E, 13,//'-',
  0x55, 29,//'=',50
  0x5D, 60,//'\',
  0x29, 00,//' ',
  0x54, 59,//'[',
  0x5B, 61,//']',
  0x4C, 27,//';',
  0x52, 7,//'''',
  0x41, 12,//',',
  0x49, 14,//'.',
  0x4A, 15,//'/',
  0x71, 14,//'.',60
};
const prog_char  Shifted[] = {
  0x1C,33,//'A',
  0x32,34,//'B',
  0x21,35,//'C',
  0x23,36,// 'D',
  0x24,37,// 'E',
  0x2B,38,// 'F',
  0x34,39,// 'G',
  0x33,40,// 'H',
  0x43,41,// 'I',
  0x3B,42,// 'J',
  0x42,43,// 'K',
  0x4B,44,// 'L',
  0x3A,45,// 'M',
  0x31,46,// 'N',
  0x44,47,// 'O',
  0x4D,48,// 'P',
  0x15,49,// 'Q',
  0x2D,50,// 'R',
  0x1B,51,// 'S',
  0x2C,52,// 'T',
  0x3C,53,// 'U',
  0x2A,54,// 'V',
  0x1D,55,// 'W',
  0x22,56,// 'X',
  0x35,57,// 'Y',
  0x1A,58,// 'Z',

  0x45,9,// ')',
  0x16,1,// '!',
  0x1E,32,// '@',
  0x26,3,// '#',
  0x25,4,// '$',
  0x2E,5,// '%',
  0x36,62,// '^',
  0x3D,6,// '&',
  0x3E,10,// '*',
  0x46,8,// '(',	 
  
  0x4e,63,// '_',
  0x4E,63,// '_',
  0x55,11,// '+',
  0x5D,91,// '|',
  0x29,00,// ' ',
  0x29,00,// ' ',
  0x29,00,// ' ',
  0x4C,26,// ':',
  0x29,00,// '',
  0x41,28,// '<',
  0x49,30,// '>',
  0x4A,31,// '?',
  0x71,14,// '.',

  0x70,16,// '0',
  0x69,17,// '1',
  0x72,18,// '2',
  0x7A,19,// '3',
  0x6B,20,// '4',
  0x73,21,// '5',
  0x74,22,// '6',
  0x6C,23,// '7',
  0x75,25,// '8',
  0x7D,26,// '9',
};
const prog_char  font6x8[] =
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// sp
    0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,// !
    0x00, 0x00, 0x07, 0x00, 0x07, 0x00,// "
    0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,// #
    0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,// $
    0x00, 0x62, 0x64, 0x08, 0x13, 0x23,// %
    0x00, 0x36, 0x49, 0x55, 0x22, 0x50,// &
    0x00, 0x00, 0x05, 0x03, 0x00, 0x00,// '
    0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,// (
    0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,// )
    0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,// *
    0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,// +
    0x00, 0x00, 0x00, 0xA0, 0x60, 0x00,// ,
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08,// -
    0x00, 0x00, 0x60, 0x60, 0x00, 0x00,// .
    0x00, 0x20, 0x10, 0x08, 0x04, 0x02,// /
    0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
    0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,// 1
    0x00, 0x42, 0x61, 0x51, 0x49, 0x46,// 2
    0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,// 3
    0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,// 4
    0x00, 0x27, 0x45, 0x45, 0x45, 0x39,// 5
    0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
    0x00, 0x01, 0x71, 0x09, 0x05, 0x03,// 7
    0x00, 0x36, 0x49, 0x49, 0x49, 0x36,// 8
    0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,// 9
    0x00, 0x00, 0x36, 0x36, 0x00, 0x00,// :
    0x00, 0x00, 0x56, 0x36, 0x00, 0x00,// ;
    0x00, 0x08, 0x14, 0x22, 0x41, 0x00,// <
    0x00, 0x14, 0x14, 0x14, 0x14, 0x14,// =
    0x00, 0x00, 0x41, 0x22, 0x14, 0x08,// >
    0x00, 0x02, 0x01, 0x51, 0x09, 0x06,// ?
    0x00, 0x32, 0x49, 0x59, 0x51, 0x3E,// @
    0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,// A
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,// B
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,// C
    0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,// D
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,// E
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,// F
    0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,// G
    0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,// H
    0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,// I
    0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,// J
    0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,// K
    0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,// L
    0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,// M
    0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,// N
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,// O
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,// P
    0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
    0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,// R
    0x00, 0x46, 0x49, 0x49, 0x49, 0x31,// S
    0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,// T
    0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,// U
    0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,// V
    0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,// W
    0x00, 0x63, 0x14, 0x08, 0x14, 0x63,// X
    0x00, 0x07, 0x08, 0x70, 0x08, 0x07,// Y
    0x00, 0x61, 0x51, 0x49, 0x45, 0x43,// Z
    0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,// [
    0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55,// 55
    0x00, 0x00, 0x41, 0x41, 0x7F, 0x00,// ]
    0x00, 0x04, 0x02, 0x01, 0x02, 0x04,// ^
    0x00, 0x40, 0x40, 0x40, 0x40, 0x40,// _
    0x00, 0x00, 0x01, 0x02, 0x04, 0x00,// '
    0x00, 0x20, 0x54, 0x54, 0x54, 0x78,// a
    0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,// b
    0x00, 0x38, 0x44, 0x44, 0x44, 0x20,// c
    0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,// d
    0x00, 0x38, 0x54, 0x54, 0x54, 0x18,// e
    0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,// f
    0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,// g
    0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,// h
    0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,// i
    0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,// j
    0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,// k
    0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,// l
    0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,// m
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,// n
    0x00, 0x38, 0x44, 0x44, 0x44, 0x38,// o
    0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,// p
    0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,// q
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,// r
    0x00, 0x48, 0x54, 0x54, 0x54, 0x20,// s
    0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,// t
    0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,// u
    0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,// v
    0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,// w
    0x00, 0x44, 0x28, 0x10, 0x28, 0x44,// x
    0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,// y
    0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,// z
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14// horiz lines
  }; 
const prog_char  shuzi[]={
  /*--  文字:  0  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,

  /*--  文字:  1  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,

  /*--  文字:  2  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,

  /*--  文字:  3  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,

  /*--  文字:  4  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,

  /*--  文字:  5  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,

  /*--  文字:  6  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,

  /*--  文字:  7  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,

  /*--  文字:  8  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,

  /*--  文字:  9  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,

  /*--  文字:  a  --10*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,

  /*--  文字:  b  --11*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,

  /*--  文字:  c  --12*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,

  /*--  文字:  d  --13*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,

  /*--  文字:  e  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,

  /*--  文字:  f  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,

  /*--  文字:  g  --16*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,

  /*--  文字:  h  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,

  /*--  文字:  i  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,

  /*--  文字:  j  --19*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,

  /*--  文字:  k  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,

  /*--  文字:  l  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,

  /*--  文字:  m  --22*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,

  /*--  文字:  n  --23*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,

  /*--  文字:  o  --24*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,

  /*--  文字:  p  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,

  /*--  文字:  q  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,

  /*--  文字:  r  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,
																			   
  /*--  文字:  s  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,

  /*--  文字:  t  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,

  /*--  文字:  u  --30*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,

  /*--  文字:  v  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,

  /*--  文字:  w  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,

  /*--  文字:  x  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,

  /*--  文字:  y  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,

  /*--  文字:  z  --35*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,

  /*--  文字:  -  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,

  /*--  文字:  =  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,

  /*--  文字:  \  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,

  /*--  文字:     --39*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

  /*--  文字:  [  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,

  /*--  文字:  ]  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,

  /*--  文字:  ;  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,

  /*--  文字:  '  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

  /*--  文字:  ,  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,

  /*--  文字:  .  --45*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,

  /*--  文字:  /  --*/
  /*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
  0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,

};
const prog_char  hanzi[]=
  {
    /*--  文字:  请  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x40,0x42,0x4C,0xC4,0x00,0x22,0xAA,0xAA,0xAA,0xBF,0xAA,0xAA,0xAA,0x22,0x20,0x00,
    0x00,0x00,0x00,0x7F,0x20,0x10,0xFF,0x0A,0x0A,0x0A,0x4A,0x8A,0x7F,0x00,0x00,0x00,

    /*--  文字:  插  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x08,0x08,0x08,0xFF,0x88,0x48,0x92,0x92,0x52,0x12,0xFE,0x11,0x91,0x91,0x90,0x00,
    0x02,0x42,0x81,0x7F,0x00,0x00,0x7F,0x24,0x24,0x20,0x3F,0x20,0x24,0x24,0x7F,0x00,

    /*--  文字:  上  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
    0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x60,0x40,0x00,

    /*--  文字:  接  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x08,0x08,0x08,0xFF,0x88,0x68,0x24,0x2C,0xB4,0x25,0x26,0x34,0x2C,0x24,0x20,0x00,
    0x02,0x42,0x81,0x7F,0x02,0x82,0x8A,0x4E,0x53,0x32,0x12,0x2E,0x42,0xC2,0x02,0x00,

    /*--  文字:  口  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x00,0x00,0xFC,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0xFC,0x00,0x00,0x00,
    0x00,0x00,0x3F,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3F,0x00,0x00,0x00,

    /*--  文字:  键  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x40,0x30,0xEF,0x28,0x28,0x44,0x64,0xDC,0x10,0x54,0xFF,0x54,0x54,0x7C,0x10,0x00,
    0x01,0x01,0x7F,0x21,0x51,0x22,0x14,0x0F,0x14,0x25,0x3F,0x45,0x45,0x45,0x44,0x00,

    /*--  文字:  盘  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x20,0x20,0xA0,0x7C,0x24,0x26,0x6D,0xB4,0x24,0x24,0x24,0xFC,0x20,0x20,0x20,0x00,
    0x44,0x42,0x41,0x7C,0x44,0x44,0x7C,0x45,0x44,0x7D,0x46,0x45,0x7C,0x40,0x40,0x00,

    /*--  文字:  并  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x00,0x10,0x10,0x11,0x12,0xFC,0x14,0x10,0x10,0x10,0xF8,0x17,0x12,0x10,0x00,0x00,
    0x00,0x01,0x81,0x41,0x31,0x0F,0x01,0x01,0x01,0x01,0xFF,0x01,0x01,0x01,0x01,0x00,

    /*--  文字:  按  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x10,0x10,0x10,0xFF,0x90,0x50,0x98,0x88,0x88,0xE9,0x8E,0x88,0x88,0x98,0x88,0x00,
    0x02,0x42,0x81,0x7F,0x00,0x40,0x40,0x26,0x25,0x18,0x08,0x16,0x31,0x60,0x20,0x00,

    /*--  文字:  你  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x80,0x40,0xF0,0x2C,0x43,0x20,0x98,0x0F,0x0A,0xE8,0x08,0x88,0x28,0x1C,0x08,0x00,
    0x00,0x00,0x7F,0x00,0x10,0x0C,0x03,0x21,0x40,0x3F,0x00,0x00,0x03,0x1C,0x08,0x00,

    /*--  文字:  已  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x00,0x00,0xE2,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x7E,0x00,0x00,0x00,0x00,
    0x00,0x00,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3C,0x10,0x00,

    /*--  文字:  经  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x20,0x30,0xAC,0x63,0x10,0x00,0x40,0x42,0x22,0x22,0x12,0x1A,0x26,0x42,0xC0,0x00,
    0x22,0x23,0x22,0x12,0x12,0x00,0x20,0x21,0x21,0x21,0x3F,0x21,0x21,0x21,0x20,0x00,

    /*--  文字:  下  --*/
    /*--  Trebuchet MS12;  此字体下对应的点阵为：宽x高=16x16   --*/
    0x00,0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x22,0x62,0xC2,0x82,0x02,0x03,0x02,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,

  };

//---------------------------------------
//名称: 使用SPI接口写数据到LCD
//参数：dt：写入的数据 command: 1-数据/0-命令
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20100202  
//-----------------------------------------  
void LCD_write_byte(unsigned char dt, unsigned char command)
{
  SPCR=0x50;	 	
  sce0; 	
  if(command)
    dc1;
  else
    dc0;		
  SPDR=dt;  //start sending data
  while((SPSR>>7)==0); //wait for the sending and receiving end
}
//---------------------------------------
//名称: 5110LCD初始化函数
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20100202
//----------------------------------------- 
void LCD_init(void)
{
  LCD_write_byte(0x21,0);//LCD功能设置：芯片活动，水平寻址，使用扩展指令
  LCD_write_byte(0xc0,0);//设置VOP值
  LCD_write_byte(0x20,0);//LCD功能设置：芯片活动，水平寻址，使用基本指令
  LCD_write_byte(0x0C,0);//设定显示配置:普通模式
  sce1;
}
//---------------------------------------
//名称: 设置坐标函数
//参数：X：0－83 Y：0－5
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20100202 
//-----------------------------------------   
void LCD_set_XY(unsigned char X, unsigned char Y)
{
  LCD_write_byte(0x40 | Y, 0);// column
  LCD_write_byte(0x80 | X, 0);// row
  sce1;
} 
//---------------------------------------
//名称: LCD清屏函数
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20100202
//----------------------------------------- 
void LCD_clear(void)
{
  unsigned char t;
  unsigned char k;
  LCD_set_XY(0,0);
  for(t=0;t<6;t++)
    { 
      for(k=0;k<84;k++)
        { 
          LCD_write_byte(0x00,1);	 						
        } 
    }
  sce1;
}
//---------------------------------------
//名称: 显示英文字符
//参数：c：显示的字符在font6x8表格中的位置
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20100202
//-----------------------------------------  	
void LCD_write_char(unsigned char row, unsigned char page,unsigned char c)
{
  unsigned char line;	
  LCD_set_XY(row*8, page);// 列，页 
  for (line=0; line<6; line++)
    LCD_write_byte(pgm_read_byte(font6x8+c*6+line), 1);	
  LCD_write_byte(0x00,1);
  LCD_write_byte(0x00,1);
}

//---------------------------------------
//名称: 写一个字符到LCD函数（8*16点阵）
//参数：row,page：写入字符的地址 c: 写入字符在shuzi表格中的位置
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20100202 
void LCD_write_shu(unsigned char row, unsigned char page,unsigned char c) //row:列 page:页 dd:字符
{
  unsigned char i;  	
	
  LCD_set_XY(row*8, page);// 列，页 
  for(i=0; i<8;i++) 
    {
      LCD_write_byte(pgm_read_byte(shuzi+c*16+i),1); 
    }
	
  LCD_set_XY(row*8, page+1);// 列，页 
  for(i=8; i<16;i++) 
    {
      LCD_write_byte(pgm_read_byte(shuzi+c*16+i),1);
    }
  sce1;
}
//---------------------------------------
//名称: 写一个汉字到LCD函数
//参数：x,y：写入汉字的地址 address: 写入汉字在han表格中的位置
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20100202 
//----------------------------------------- 
void LCD_write_hanzi(unsigned char row, unsigned char page,unsigned char c) //row:列 page:页 dd:字符
{
  unsigned char i;  	
	
  LCD_set_XY(row*8, page);// 列，页 
  for(i=0; i<16;i++) 
    {
      LCD_write_byte(pgm_read_byte(hanzi+c*32+i),1); 		
    }

  LCD_set_XY(row*8, page+1);// 列，页 
  for(i=16; i<32;i++) 
    {
      LCD_write_byte(pgm_read_byte(hanzi+c*32+i),1);
    }	
  sce1;
}
unsigned char  Decode(unsigned char ScanCode)
//注意:如SHIFT+G为12H 34H F0H 34H F0H 12H?
//也就是说shift的通码+G的通码+shift的断码+G的断码
{
  unsigned char TempCyc; 
  unsigned char KeyChar=0;
  if (!Key_UP) //当键盘松开时
    {
      switch (ScanCode)
        {
        case 0xF0 : // 当收到0xF0，Key_UP置1表示断码开始
          Key_UP = 1;
          break;

        case 0x12 : // 左 SHIFT
          Shift = 1;
          break;

        case 0x59 : // 右 SHIFT
          Shift = 1;
          break;
        case 0x66:  //backspace
          disbuf=0;
          disbit=1;							
          break;
        default: 
          if (DisNum > 15) DisNum = 0; 
          if(!Shift) //如果SHIFT没按下
            {
              for(TempCyc = 0; (pgm_read_byte(UnShifted+TempCyc*2)!=ScanCode)&&(TempCyc<59); TempCyc++); //查表显示
              if (pgm_read_byte(UnShifted+TempCyc*2) == ScanCode) 
                {
                  KeyChar=pgm_read_byte(UnShifted+TempCyc*2+1);
                  disbit=1;
                  disbuf=KeyChar;											
                }		
              DisNum++;
            } 
          else //按下SHIFT
            {
              for(TempCyc = 0; (pgm_read_byte(Shifted+TempCyc*2)!=ScanCode)&&(TempCyc<59); TempCyc++); //查表显示
              if (pgm_read_byte(Shifted+TempCyc*2) == ScanCode) 
                {
                  KeyChar=pgm_read_byte(Shifted+TempCyc*2+1);
                  disbit=1;
                  disbuf=KeyChar;										
                }
              DisNum++;
            }
          break;
     	}
    }
  else
    { 
      Key_UP = 0;
      switch (ScanCode) //当键松开时不处理判码，如G 34H F0H 34H 那么第二个34H不会被处理
        {
        case 0x12 : // 左 SHIFT
          Shift = 0;
          break;
        case 0x59 : // 右 SHIFT
          Shift = 0;
          break;
        }
    }
  return KeyChar;
} 		  
void scakey(void)
{		
  if (bf) {				
    Decode(keybuf);
    bf=0;			
    sei();		
  }
  else
    sei();
}
ISR(INT1_vect) {
  if ((IntNum > 0) && (IntNum < 9)) { 
    KeyV = KeyV >> 1; //因键盘数据是低>>高，结合上一句所以右移一位
    if (Key_Data) KeyV = KeyV | 0x80; //当键盘数据线为1时为1到最高位
  }
  IntNum++;
  while (!Key_CLK); //等待PS/2CLK拉高
  if (IntNum > 10) {
    IntNum = 0; //当中断11次后表示一帧数据收完，清变量准备下一次接收
    bf = 1; //标识有字符输入完了 
    keybuf=KeyV;
    KeyV=0;		 	
  }
}

//---------------------------------------
//名称: 主函数
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20100202 
int main(void) {
  unsigned int a;
  unsigned int b;
  unsigned int c;
  unsigned int i, j;
  unsigned int f;
  unsigned char str[5] = {0};
  
  DDRC  = 0x16;
  DDRB  = 0x3a;
  DDRD  = 0x00;
  rst0;
  _delay_ms(10);	
  rst1;	
  LCD_init();  //initialize the LCD module
  LCD_clear(); 	//clear the screen
 
  hc138dis;	//disability 74HC138, to close the digital tube, LED
  wdt_enable(WDTO_2S);	//enable watchdog, 2 seconds Reset
  MCUCR=0X08;
  GICR=0X80;
  sei();
  i = 0;
  j = 1;
  a = 0;
  b = 0;
  f = 0;
  LCD_clear();
  while(1) {   
    wdt_reset();  //feed the dog commands
    scakey();
    if(disbit)
      {
        disbit=0;

        if(disbuf >= 16 && disbuf <= 25) {
          if(f == 0) {
            a *= 10;
            a += (disbuf - 16);
            LCD_write_char(i,0,disbuf);
            i++;
          }
          else {
            b *= 10;
            b += (disbuf - 16);
            LCD_write_char(i,0,disbuf);
            i++;
          }
        }
        else if(disbuf == 13 || disbuf == 11 || disbuf == 10 || disbuf == 16) {
          LCD_clear();
          j = disbuf;
          f = 1;
          i = 0;
        }
        else if(disbuf == 29) {
          if(j == 13) {
            c = a - b;
          }
          else if(j == 11) {
            c = a + b;
          }
          else if(j == 10) {
            c = a * b;
          }
          else if(j == 16) {
            c = a / b;
          }
          for(i = 0; i < 5; i++) {
            if(c == 0)
              break;
            str[i] = (c % 10) + 16;
            c /= 10;
          }
          LCD_clear();
          j = 0;
          while(i > 0) {
            LCD_write_char(i-1,0,str[j]);
            i--;
            j++;
          }
          f = 0;
          i = 0;
          a = 0;
          b = 0;
        }
        else if(disbuf == 0x00) {
          f = 0;
          i = 0;
          a = 0;
          b = 0;
          LCD_clear();
        }
      }	
  }
}

//������� ��� ������ � ������
#define PORT_DATA PORTC
#define PIN_DATA  PINC
#define DDRX_DATA DDRC

//���� � �������� ���������� ����������� ������ ���
#define PORT_SIG PORTC
#define PIN_SIG  PINC
#define DDRX_SIG DDRC

//������ ������� � ������� ���������� ����������� ������ ��� 
#define RS 0
#define RW 1
#define EN 2

//#define CHECK_FLAG_BF
#define BUS_4BIT
#define HD44780
//******************************************************************************
//�������

/*���������������� �������*/
#define LCD_Goto(x,y) LCD_WriteCom(((((y)& 1)*0x40)+((x)& 15))|128) 
#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))
#define SetBit(reg, bit)         reg |= (1<<(bit))	

#define FLAG_BF 7

inline unsigned char __swap_nibbles(unsigned char data)
{
  asm volatile("swap %0" : "=r" (data) : "0" (data));
  return data;
}

void LCD_WriteComInit(unsigned char data)
{
  _delay_us(40);
  ClearBit(PORT_SIG, RS);	
#ifdef BUS_4BIT
  unsigned char tmp; 
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);
  PORT_DATA = tmp;		 
#else
  PORT_DATA = data;		
#endif  
  SetBit(PORT_SIG, EN);	        
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	
}


inline static void LCD_CommonFunc(unsigned char data)
{
#ifdef BUS_4BIT  
  unsigned char tmp; 
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);

  PORT_DATA = tmp;		//����� ������� ������� 
  SetBit(PORT_SIG, EN);	        
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	

  data = __swap_nibbles(data);
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);
 
  PORT_DATA = tmp;		//����� ������� ������� 
  SetBit(PORT_SIG, EN);	        
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	 
#else 
  PORT_DATA = data;		    //����� ������ �� ���� ���������� 
  SetBit(PORT_SIG, EN);	     //��������� E � 1
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	//��������� E � 0 - ������������ �����
#endif
}

//������� ������ ������� 
void LCD_WriteCom(unsigned char data)
{
  ClearBit(PORT_SIG, RS);	//��������� RS � 0 - �������
  LCD_CommonFunc(data);
  _delay_ms(3);
}

//������� ������ ������
void LCD_WriteData(unsigned char data)
{
  SetBit(PORT_SIG, RS);	    //��������� RS � 1 - ������
  LCD_CommonFunc(data);
  _delay_ms(1);
}

//ooieoey eieoeaeecaoee
void LCD_Init(void)
{
#ifdef BUS_4BIT
  DDRX_DATA |= 0xf0;
  PORT_DATA |= 0xf0; 
#else  
  DDRX_DATA |= 0xff;
  PORT_DATA |= 0xff;
#endif
  
  DDRX_SIG |= (1<<RW)|(1<<RS)|(1<<EN);
  PORT_SIG |= (1<<RW)|(1<<RS)|(1<<EN);
  ClearBit(PORT_SIG, RW);
  _delay_ms(40);
  
#ifdef HD44780  
  LCD_WriteComInit(0x30); 
  _delay_ms(10);
  LCD_WriteComInit(0x30);
  _delay_ms(1);
  LCD_WriteComInit(0x30);
#endif
  
#ifdef BUS_4BIT  
  LCD_WriteComInit(0x20); //4 ��������� ����
  LCD_WriteCom(0x28); //4-��������� ����, 2 - ������
#else
  LCD_WriteCom(0x38); //8-��������� ����, 2 - ������
#endif
  LCD_WriteCom(0x08);
  LCD_WriteCom(0x0c);  //������� ���, ������ � �������� ���������
  LCD_WriteCom(0x01);  //0b00000001 - ������� �������
  _delay_ms(2);
  LCD_WriteCom(0x06);  //0b00000110 - ������ �������� ������, ������ ���
}


//������� ������ ������ �� ���� ������

//������ ������ ������ �� RAM
void LCD_SendString(char *str)
{
  unsigned char data;
  SetBit(PORT_SIG, RS);			
  while (*str)
  {
    data = *str++;
    SetBit(PORT_SIG, RS);			
    LCD_CommonFunc(data);
  }
}


void LCD_Clear(void)
{
  LCD_WriteCom(0x01);
  _delay_ms(2);
}

//макросы для работы с битами
#define PORT_DATA PORTC
#define PIN_DATA  PINC
#define DDRX_DATA DDRC

//порт к которому подключены управляющие выводы ЖКД
#define PORT_SIG PORTC
#define PIN_SIG  PINC
#define DDRX_SIG DDRC

//Номера выводов к которым подключены управляющие выводы ЖКД 
#define RS 0
#define RW 1
#define EN 2

//#define CHECK_FLAG_BF
#define BUS_4BIT
#define HD44780
//******************************************************************************
//макросы

/*позиционирование курсора*/
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

  PORT_DATA = tmp;		//вывод старшей тетрады 
  SetBit(PORT_SIG, EN);	        
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	

  data = __swap_nibbles(data);
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);
 
  PORT_DATA = tmp;		//вывод младшей тетрады 
  SetBit(PORT_SIG, EN);	        
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	 
#else 
  PORT_DATA = data;		    //вывод данных на шину индикатора 
  SetBit(PORT_SIG, EN);	     //установка E в 1
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	//установка E в 0 - записывающий фронт
#endif
}

//функция записи команды 
void LCD_WriteCom(unsigned char data)
{
  ClearBit(PORT_SIG, RS);	//установка RS в 0 - команды
  LCD_CommonFunc(data);
  _delay_ms(3);
}

//функция записи данных
void LCD_WriteData(unsigned char data)
{
  SetBit(PORT_SIG, RS);	    //установка RS в 1 - данные
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
  LCD_WriteComInit(0x20); //4 разрядная шина
  LCD_WriteCom(0x28); //4-разрядная шина, 2 - строки
#else
  LCD_WriteCom(0x38); //8-разрядная шина, 2 - строки
#endif
  LCD_WriteCom(0x08);
  LCD_WriteCom(0x0c);  //дисплей вкл, курсор и мерцание выключены
  LCD_WriteCom(0x01);  //0b00000001 - очистка дисплея
  _delay_ms(2);
  LCD_WriteCom(0x06);  //0b00000110 - курсор движется вправо, сдвига нет
}


//функция вывода строки из флэш памяти

//фунция вывода строки из RAM
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

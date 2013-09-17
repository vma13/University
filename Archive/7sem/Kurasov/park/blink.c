#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define ADC_MAX 255
#define LED_NUM 14
unsigned int error;

//Convert ADC Data and out to PORTD and PORTB
void park(unsigned int adc) {
	int led_num = (int)floor((adc * LED_NUM / ADC_MAX) + 0.5);
	unsigned int out = 0x3FFF;
	//out=pow(2, led_num)-1;
        out <<= led_num;
	//out <<= LED_NUM - led_num;


	PORTD = (char)out;
	PORTB = (char)(out >> 8);
}

ISR(ADC_vect) {
	unsigned int adc_val = ADCW;
	adc_val -= 150;
  park(adc_val);  
  ADCSRA |= (1 << ADSC);
}


void init(void) {
//Paralel IN/OUT Ports Init
	DDRB = 0x3F;
	PORTB = 0x3F;
	DDRD = 0xFF;
	PORTD = 0xFF;
//ADC Init
	ADMUX = (1 << REFS0); //AVCC with external capacitor at AREF pin
	ADCSRA = 0xCF;
//Global Interrupts Enable
	sei();
}

int main(void) {
	init();
	while (1);
	return 0;
}




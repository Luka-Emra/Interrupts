/*
 * Lab7.c
 *
 * Created: 12/4/2020 12:56:31 AM
 * Author : Luka Emrashvili
 * Red ID: 823 355 800
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

int main(void) 
{
	KeyPadInit();
	cli();
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS02) | (1<<CS00);
	TIMSK0 |= (1 << OCIE0A);
	OCR0A=62;
	
	sei();
	TCCR1A |= (1<<WGM21);
	TCCR1B |= (1<< CS22);
	
	TIMSK1 |= (1 << OCIE1A);
	TIMSK1 |= (1 << OCIE1B);
	OCR2A=88;
	
	while (1)
	{
		
	}
}
void KeyPadInit(){
	DDRD |= (1<<DDD4);
	DDRD |= (1<<DDD5);
	DDRD |= (1<<DDD6);
	DDRD |= (1<<DDD7);		
		
	DDRB &= ~(1<<DDB0);
	DDRB &= ~(1<<DDB1);
	DDRB &= ~(1<<DDB2);
	DDRB &= ~(1<<DDB3);	
		
	PORTB |= (1<<PORTB0);
	PORTB |= (1<<PORTB1);
	PORTB |= (1<<PORTB2);
	PORTB |= (1<<PORTB3);
		
	PORTD |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
		
	DDRB |= (1<<DDB5);

}
	
ISR (TIMER0_COMPA_vect) 
{
	int KeypadInput[4][4]={{1,2,3,0},{4,5,6,0},{7,8,9,0},{0,0,0,0}};
	int rows, columns;
	for (rows=0; rows<=3;rows++)
	{
		
		PORTD &=~(1<<(rows+4));
		
		for (columns=0; columns<3; columns++){
			if (!(PINB&(1<<columns))){
				switch(KeypadInput[rows][columns])
				{
					case 0:
						OCR1B=0;
						break;
					case 1:
					    OCR1B=4;
						break;				
					case 2:
						OCR1B=11;
						break;
					case 3:
					    OCR1B=18;
						break;		
					case 4:
						OCR1B=25;
						break;
					case 5:
					    OCR1B=32;
						break;			
					case 6:
						OCR1B=39;
						break;
					case 7:
					    OCR1B=46;
						break;		
					case 8:
						OCR1B=53;
						break;
					case 9:
					    OCR1B=60;
						break;				
				}
			}
		}
		
		PORTD |= (1<<(rows+4));
	}	
}

ISR(TIMER1_COMPA_vect){
	
	PORTB |= (1 << 5);
}

ISR(TIMER1_COMPB_vect){
	
	PORTB &= ~(1 << 5);
}

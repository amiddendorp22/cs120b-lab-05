/*	Author: amidd001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;
void TimerISR()
{
	TimerFlag = 1;
}

enum SM_States {SM_Init, SM_PA0, SM_Wait1, SM_Wait2, SM_PA1, SM_Wait3, SM_Both} SM_State;

void TickFct_Press()
{

	switch(SM_State) //transitions
	{
		unsigned char tmpA = ~PINA & 0x03;
		case(SM_Init):
			if(tmpA == 0x00)
			{
				SM_State = SM_Init;	
			}
			else if(tmpA == 0x01)
			{
				SM_State = SM_PA0;
			}
			else if(tmpA == 0x02)
			{
				SM_State = SM_PA1;
			}
			else if(tmpA == 0x03)
			{
				SM_State = SM_Both;
			}
			break;
		case(SM_PA0):
			SM_State = SM_Wait1;
			break;
		case(SM_Wait1):
			if(tmpA == 0x01)
			{
				SM_State = SM_PA0;
			}
			else if(tmpA == 0x02)
			{
				SM_State = SM_PA1;
			}
			else if(tmpA == 0x03)
			{
				SM_State = SM_Both;
			}
			else if(tmpA == 0x00)
			{
				SM_State = SM_Wait1;
			}
			break;
		case(SM_Wait2):
			if(tmpA == 0x00)
			{
				SM_State = SM_Wait2;
			}
			else if(tmpA == 0x01)
			{
				SM_State = SM_PA0;
			}
			else if(tmpA == 0x02)
			{
				SM_State = SM_PA1;
			}
			else if(tmpA == 0x03)
			{
				SM_State = SM_Both;
			}
			break;
		case(SM_PA1):
			SM_State = SM_Wait2;
			break;
		case(SM_Both):
			SM_State = SM_Wait3;
			break;
		case(SM_Wait3):
			if(tmpA == 0x00)
			{
				SM_State = SM_Wait3;
			}
			else if(tmpA == 0x01)
			{
				SM_State = SM_PA0;
			}
			else if(tmpA == 0x02)
			{
				SM_State = SM_PA1;
			}
			else if(tmpA == 0x03)
			{
				SM_State = SM_Both;
			}
			break;
		default:
			break;
	}


	switch(SM_State) //State actions
	{
		case(SM_Init):
			PORTC = 0x07;
			//PORTB = 0x01;
			break;
		case(SM_PA0):
			if(PORTC != 0x09 && PINA != 0x03)
			{
				PORTC = PORTC + 1;
				PORTB = 0x00;
			}
			else if(PORTC != 0x09)
			{
				PORTC = PORTC + 1;
				PORTB = 0x00;

			}
			if(PINA == 0x03)
			{
				PORTC = 0x00;
				PORTB = 0x00;

			}
			break;
		case(SM_Wait1):
			PORTB = 0x00;
			break;
		case(SM_Wait2):
			PORTB = 0x00;
			break;
		case(SM_PA1):
			if(PORTC == 0)
			{
				PORTB = 0x00;
				break;
			}
			else if(PINA == 0x03)
			{
				PORTB = 0x00;
				PORTC = 0x00;
			}
			else
			{
				PORTB = 0x00;
				PORTC = PORTC - 1;
			}
			break;
		case(SM_Wait3):
			PORTB = 0x00;
			break;
		case(SM_Both):
			PORTB = 0x00;
			PORTC = 0;
			break;
		default:
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //sets PINA as input
    DDRB = 0xFF; PORTB = 0x00; //sets PORTB as output
    DDRC = 0xFF; PORTC = 0x00; //sets PORTC as output
    /* Insert your solution below */
    SM_State = SM_Init;
    PORTC = 0x07;
    while (1) {
	TickFct_Press();
	//TimerTick();
    }
    return 1;
}

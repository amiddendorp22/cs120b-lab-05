/*	Author: amidd001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *	Video Demo Link : https://www.youtube.com/watch?v=MHJbvrT7Gq0
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum SM_States {SM_Init, SM_Off, SM_One, SM_Two, SM_Three, SM_Four, SM_Five, SM_Six } SM_State;

void TickFct_Lights()
{
	unsigned char tmpA = ~PINA & 0x01;
	switch(SM_State)
	{
		case(SM_Init):
			if(tmpA == 0x01)
			{
				SM_State = SM_Off;
			}
			else
			{
				SM_State = SM_Init;
			}
			break;
		case(SM_Off):
			if(tmpA == 0x01)
			{
				SM_State = SM_One;
			}
			else
			{
				SM_State = SM_Off;
			}
			break;
		case(SM_One):
			if(tmpA == 0x01)
			{
				SM_State = SM_Two;
			}
			else
			{
				SM_State = SM_One;
			}
			break;
		case(SM_Two):
			if(tmpA == 0x01)
			{
				SM_State = SM_Three;
			}
			else
			{
				SM_State = SM_Two;
			}
			break;
		case(SM_Three):
			if(tmpA == 0x01)
			{
				SM_State = SM_Four;
			}
			else
			{
				SM_State = SM_Three;
			}
			break;
		case(SM_Four):
			if(tmpA == 0x01)
			{
				SM_State = SM_Five;
			}
			else
			{
				SM_State = SM_Four;
			}
			break;
		case(SM_Five):
			if(tmpA == 0x01)
			{
				SM_State = SM_Six;
			}
			else
			{
				SM_State = SM_Five;
			}
			break;
		case(SM_Six):
			if(tmpA == 0x01)
			{
				SM_State = SM_Off;
			}
			else
			{
				SM_State = SM_Six;
			}
			break;
	}

	switch(SM_State)
	{
		case(SM_Init):
			PORTC = 0xFF;
			break;
		case(SM_Off):
			PORTC = 0x00;
			break;
		case(SM_One):
			PORTC = 0x01;
			break;
		case(SM_Two):
			PORTC = 0x03;
			break;
		case(SM_Three):
			PORTC = 0x07;
			break;
		case(SM_Four):
			PORTC = 0x0F;
			break;
		case(SM_Five):
			PORTC = 0x1F;
			break;
		case(SM_Six):
			PORTC = 0x3F;
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
    PORTC = 0x00;
    unsigned char incrementPressed = 0x00;
    unsigned char tmpA;
    while (1) {
	tmpA = ~PINA & 0x01;
	if(tmpA == 0x01 && (incrementPressed != 0x01))
	{
		incrementPressed = 0x01;
		TickFct_Lights();
	}
	if(tmpA == 0x00)
	{
		incrementPressed = 0x00;
	}
    }
    return 1;
}

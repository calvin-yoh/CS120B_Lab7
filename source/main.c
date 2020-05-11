/*	Author: lab
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "io.h"
#endif

void Tick();
enum States { Start, FIRST, SECOND, THIRD, SECONDSECOND, STOP, RESTART } state;
unsigned char tempA = 0x00;
unsigned char tempB = 0x00;
unsigned char currScore = 0x05;

int main(void)
{
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	DDRC = 0xFF;	PORTC = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;
	state = Start;
	TimerSet(300);
	TimerOn();
	LCD_init();
	LCD_WriteData(currScore + '0');
	while (1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}

void Tick()
{
	tempA = ~PINA;
	switch (state) //Transitions
	{
	case Start:
	{
		tempB = 0x00;
		state = FIRST;
		break;
	}
	case FIRST:
	{
		if (tempA == 0x01)
		{
			state = STOP;
			break;
		}
		else
		{
			state = SECOND;
			break;
		}
	}
	case SECOND:
	{
		if (tempA == 0x01)
		{
			state = STOP;
			break;
		}
		else
		{
			state = THIRD;
			break;
		}
	}
	case THIRD:
	{
		if (tempA == 0x01)
		{
			state = STOP;
			break;
		}
		else
		{
			state = SECONDSECOND;
			break;
		}
	}
	case SECONDSECOND:
	{
		if (tempA == 0x01)
		{
			state = STOP;
			break;
		}
		else
		{
			state = FIRST;
			break;
		}
	}
	case STOP:
	{
		if (tempA == 0x01)
		{
			state = STOP;
			break;
		}
		else
		{
			state = RESTART;
			break;
		}
	}
	case RESTART:
	{
		if (tempA == 0x01)
		{
			state = FIRST;
			break;
		}
		else
		{
			state = RESTART;
			break;
		}

	}
	default:
		break;
	}

	switch (state) //State Actions
	{
	case FIRST:
	{
		tempB = 0x01;
		break;
	}
	case SECOND:
	{
		tempB = 0x02;
		break;
	}
	case THIRD:
	{
		tempB = 0x04;
		break;
	}
	case SECONDSECOND:
	{
		tempB = 0x02;
		break;
	}
	case STOP:
	{
		if (tempB == 0x02)
		{
			currScore++;
		}
		else
		{
			currScore--;
		}
	}
	default:
		break;
	}
	PORTB = tempB;
	LCD_Cursor(1);
	LCD_WriteData(tempB + '0');
}

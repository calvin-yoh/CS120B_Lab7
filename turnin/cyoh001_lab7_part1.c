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
#endif

void Tick();
enum States { START, FIRST, SECOND, THIRD }state;
unsigned char tempB = 0x00;

int main(void)
{
	DDRB = 0xFF;
	tempB = 0x00;
	state = START;
	TimerSet(1000);
	TimerOn();
	while (1) {
		Tick();
		// Wait 1 sec
		while (!TimerFlag);
		TimerFlag = 0;
	}
}

void Tick() {
	switch (state) { //transitions
	case START:
	{
		tempB = 0x00;
		state = FIRST;
		break;
	}
	case FIRST:
	{
		state = SECOND;
		break;
	}
	case SECOND:
	{
		state = THIRD;
		break;
	}
	case THIRD:
	{
		state = FIRST;
		break;
	}
	}
	switch (state) { //state actions
	case START:
		break;

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
	}
	PORTB = tempB;
}

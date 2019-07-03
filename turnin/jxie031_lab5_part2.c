/*	Author: jxie031
 *  Partner(s) Name: Xichao Wang
 *	Lab Section:
 *	Assignment: Lab 2  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start,A0remain,A1remain, init,A0press, A0release, A1press, A1release,reset} state;
unsigned char x;
void TickFct_Latch(){
	unsigned char PB = PORTC;
	unsigned char A1 = ~PINA & 0x02;
	unsigned char A0 = ~PINA & 0x01;
	switch(state){
	 case start:
		state = init;
		break;
	case A0remain:
		if(A0 && A1) state = reset;
		else if(A0) state = A0remain;
		else state = A0release;
		break;
	case A1remain:
		if(A0 && A1) state = reset;
		else if(A1) state = A1remain;
		else state = A1release;
		break;
	 case init:
		if(A0 && A1) state = reset;
		else if(A1) state = A1press;
		else if(A0) state = A0press;
		else state = init;
		break;
	case A0press:
		if(A0 && A1) state = reset;
		else if(A0) state = A0remain;
		else if(!A0) state = A0release;
		else state = A0remain; 
		break;
	case A0release:
		if(A0 && A1) state = reset;
                else if(A0) state = A0press;
                else if(A1) state = A1press;
                else state = A0release;
                break;
	case A1press:
                if(A0 && A1) state = reset;
                else if(!A1) state = A1release;
                else if(A1) state = A1remain;
                else state = A1remain;
                break;
	case A1release:
                if(A0 && A1) state = reset;
                else if(A0) state = A0press;
                else if(A1) state = A1press;
                else state = A1release;
                break;
	case reset:
		if(A0 && A1) state = reset;
                else if(A0) state = A0press;
                else if(A1) state = A1press;
                else state = reset;
                break;
		
	default:
		state = start;
		break; 
	}
	switch(state){
	case start:
		break;
	case A0remain:
		break;
	case A1remain:
		break;
	case init:
		PORTC = 7;
		break;
	case A0press:
		if(PB < 9)
			PORTC= PB + 1;
		break;
	case A0release:
		break;
	case A1press:
		if(PB > 0)
		PORTC = PB -1;
		break;
	case A1release:
		break;
	case reset:
		PORTC = 0;
		break;
	default:
		break;
	
	}

}
int main(void) {
DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs			
	state = start;
	// Initialize output on PORTB to 0x00
	while(1) {
		TickFct_Latch();
	}
	return 1;
}

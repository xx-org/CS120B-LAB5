/*	Author: jxie031
 *  Partner(s) Name: Xichao Wang
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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	//DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char A;

	unsigned char C = 0x00;
    /* Insert your solution below */
    while (1) {
		C = 0x00;
		A = PINA;
		if(A == 1 || A == 2)
			C = C | (0x01 << 5);
		else if (A == 3 || A == 4)
			C = C | (0x03 << 4);
		else if (A == 5 || A == 6)
			C = C | (0x07 <<3);
		else if (A == 7 || A == 8 || 7 == 9)
			C = C | (0x0F << 2);
		else if (A == 10 || A == 11 || A == 12)
			C = C | (0x1F << 1);
		else if (A == 13 || A == 14 || A == 15)
			C = C | 0x3F;
		else 
			C = C;
		if ( A <= 4)
			C = C | (0x01 << 6);
		else C = C;
			
		PORTC = C;
    }
    return 1;
}

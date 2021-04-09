/*	Author: rmose005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #1
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
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0x00; PORTC = 0xFF; // Configure port C's 8 pins as inputs
	DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs, initialize to 0s

	unsigned char tmpD = 0x00; // Temporary variable to hold the value of D
	unsigned char tmpC = 0x00; // Temporary variable to hold the value of C
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char combinedWeight = 0x00;

	while(1) {
		// 1) Read input
		tmpC = PINC;
		tmpB = PINB;
		tmpA = PINA;
		combinedWeight = tmpC + tmpB + tmpA;
		// 2) Perform computation
		if (combinedWeight > 140) // if combinedWeight > 140
			tmpD = tmpD | 0x01; // PD0 = 1
	
		if (tmpA >= tmpC) // check if tmpA or tmpC is greater to avoid overflow:
		{
			if (tmpA - tmpC > 80)
				tmpD = tmpD | 0x02; // PD1 = 1
		}
		else
		{
			if (tmpC - tmpA > 80)
				tmpD = tmpD | 0x02; // PD1 = 1
		}
	
		tmpD = (combinedWeight & 0xFC) | tmpD; // clear first two bits of combinedWeight -> retain tmpD's PD0 and PD1.
	
		// 3) Write output
		PORTB = tmpD;
	}
	return 0;
}

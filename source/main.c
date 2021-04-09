/*	Author: rmose005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #3
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
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char cntavail = 0x00;
	unsigned char i = 0x00;
	while(1) {
		// 1) Read input
		tmpA = PINA;
		// 2) Perform computation
		// for loop iterates 4 times
		cntavail = 0x00;
		for (i = 0; i < 4; ++i)
		{
			if ((tmpA & 0x01) == 0x00) { // if rightmost is 0:
				++cntavail; // space is available -> increment
			}
			tmpA = tmpA >> 1;
		}
		if (cntavail == 0) // if no spaces available (cntavail is 0):
			cntavail = cntavail | 0x80; // PC7 set to 1.
		// 3) Write output
		PORTC = (PORTC & 0x70) | cntavail; // retain PC6..PC4 -> write into PC7 and PC3..PC0
	}
	return 0;
}

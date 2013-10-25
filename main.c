#include <msp430.h> 
#include "LCDDriver.h"
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    initSPI();
	LCDinit();
	LCDclear();
	writeChar('A');
	while(1){}
}

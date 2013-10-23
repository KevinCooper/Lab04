#include <msp430.h> 
#include "LCDDriver.h"
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    initSPI();
	LCDinit();
	while(1){}
}

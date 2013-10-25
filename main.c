#include <msp430.h> 
#include "LCDDriver.h"
#include "buttons/button.h"
/*
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	//Set up the MSP430
	initSPI();
	LCDinit();
	LCDclear();

	//Initialize all the strings
	char * message = "Message?Press123";

	writeString(message);

	char * top = "ECE382 is my favorite class!    ";
	char * bottom1 = "And I sure am excited for ECE383!    ";
	char * bottom2 = "And I am excited for ECE373!    Wait.  What is going on.  Why am I trapped in this little machine!!!";
	char * bottom3 = "And I am going to Cyber after this!    ";
	char * choice;

	//Setup buttons
	configureP1PinAsButton(BIT0 | BIT1 | BIT2);
	char buttons[] = { BIT0, BIT1, BIT2 };
	char pressedButton = pollP1Buttons(buttons, 3);

	//Determine button press
	switch (pressedButton) {
	case BIT0:
		choice = bottom1;
		break;
	case BIT1:
		choice = bottom2;
		break;
	case BIT2:
		choice = bottom3;
		break;
	}
	//print top message and choice
	scrollString(top, choice);

	while (1) {
	}
}

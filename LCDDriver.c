/*
 * LCDDriver.c
 *
 *  Created on: Oct 23, 2013
 *      Author: C15Kevin.Cooper
 */

#define RS_MASK 0x40
#include <msp430.h>

void SPI_send(char byteToSend);
void writeCommandByte(char commandByte);
void writeDataByte(char dataByte);
void writeCommandNibble(char commandNibble);
void LCD_write_8(char byteToSend);
void LCD_write_4(char nibbleToSend);
void delayMilli();
void delayMicro();
void set_SS_lo();
void set_SS_hi();


char LCDCON;

short unsigned int position;

/*
 * Author: Todd Branchflower
 */
void LCDinit()
{
	LCDCON &= 0x00; //Clear out the Connection bit to a know state

	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x02);

	writeCommandByte(0x28);

	writeCommandByte(0x0C);

	writeCommandByte(0x01);

	writeCommandByte(0x06);

	writeCommandByte(0x01);

	writeCommandByte(0x02);

	SPI_send(0);
	delayMicro();
	position = 0;// Set up the position for the write bytes
}
/*
 * Author: Todd Branchflower
 */
void writeCommandNibble(char commandNibble)
{
	LCDCON &= ~RS_MASK;
	LCD_write_4(commandNibble);
	delayMilli();
}
/*
 * Author: Todd Branchflower
 */
void writeCommandByte(char commandByte)
{
	LCDCON &= ~RS_MASK;
	LCD_write_8(commandByte);
	delayMilli();
}
/*
 * Author: Todd Branchflower
 */
void writeDataByte(char dataByte)
{
	LCDCON |= RS_MASK;
	LCD_write_8(dataByte);
	delayMilli();
}
/*
 * Author: Todd Branchflower
 */
void LCD_write_8(char byteToSend)
{
	unsigned char sendByte = byteToSend;
	sendByte &= 0xF0;
	sendByte = sendByte >> 4;               // rotate to the right 4 times
	LCD_write_4(sendByte);
	sendByte = byteToSend;
	sendByte &= 0x0F;
	LCD_write_4(sendByte);
}

void LCD_write_4(char nibbleToSend)
{
	nibbleToSend &= 0x0F; //Clear upper half
	nibbleToSend |= LCDCON; //Set LCD control
	nibbleToSend &= 0x7f; //Set E low
	SPI_send(nibbleToSend);
	delayMicro();
	nibbleToSend &= 0x80;
	SPI_send(nibbleToSend);
	delayMicro();
	nibbleToSend &= 0x7f;
	SPI_send(nibbleToSend);
	delayMicro();

}

void delayMilli()
{
	__delay_cycles(222); //Delay 1.65 ms
}

void delayMicro()
{
	__delay_cycles(9);  //Delay 40.5 micro seconds
}
/*
 * Author: Todd Branchflower
 */
void SPI_send(char byteToSend)
{
	char readByte;

	set_SS_lo();

	UCB0TXBUF = byteToSend;

	while (!(UCB0RXIFG & IFG2)) {
		// wait until you've received a byte
	}

	readByte = UCB0RXBUF;

	set_SS_hi();
}

void set_SS_lo()
{
	P1OUT |= BIT0 | BIT3;
}

void set_SS_hi()
{
	P1OUT &= ~BIT0 | BIT3;
}
/*
 * Author: Kevin Cooper
 */
void initSPI()
{
	UCB0CTL1 |= UCSWRST | UCSSEL1; //select a clock to use!
	UCB0CTL0 |= UCCKPL | UCMSB | UCMST | UCSYNC;
	UCB0STAT |= UCLISTEN;  //enables internal loopback
	P1SEL |= BIT5;  //make UCB0CLK available on P1.5
	P1SEL2 |= BIT5;
	P1DIR |= BIT0 | BIT3;  //Set up P1.3 to be out SS output
	P1SEL |= BIT7;  //make UCB0SSIMO available on P1.7 ; = MOSI
	P1SEL2 |= BIT7;
	P1SEL |= BIT6; //make UCB0SSOMI available on P1.6; = MISO
	P1SEL2 |= BIT6;
	UCB0CTL1 &= ~UCSWRST; //enable subsystem
}

void cursorToLineTwo()
{
	writeCommandByte(0xA8); // Remember to take out magic number
	//Delay 1
	LCDCON |= RS_MASK;  // Because Assembly.....
	//Delay 2
}

void cursorToLineOne()
{
	writeCommandByte(0x80); // Remember to take out magic number
	//Delay 1
	LCDCON |= RS_MASK;  // Because Assembly.....
	//Delay 2
}

void LCDclear()
{
	writeCommandByte(0x01); // Remember to take out magic number
	//Delay 1
	LCDCON |= RS_MASK;  // Because Assembly.....
	//Delay 2
	position = 0;
}

void writeChar(char asciiChar){
	if(position == 20)
		cursorToLineTwo();
	if(position != 40){
		writeDataByte(asciiChar);
		position ++;
	}
}

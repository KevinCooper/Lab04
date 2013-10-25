//
// lcd.h
// Author: Todd Branchflower
// Date: 17 October 2013
// Description: Library to interact with the Geek Box LCD.
//

#ifndef LCDDRIVER_H_
#define LCDDRIVER_H_

#define LCDCON 1

void initSPI();  //Done
void LCDinit();  //Done
void LCDclear();
void cursorToLineTwo();  //Done
void cursorToLineOne();  //Done
void writeChar(char asciiChar);
void writeString(char * string);
void scrollString(char * string1, char * string2);

#endif /* LCDDRIVER_H_ */

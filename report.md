# Title

## Objective / Purpose<br>

The purpose of this lab is to design a LCD driver.  However, this driver should be a relative port from the assembly code written from Lab03.  Clean, modular, and maintanable C code is a strong emphasis to focus on when designing the API for the LCD driver code.<br>

## Preliminary Design<br>
Porting the assembly code over to C should be relatively simple, further explanation on this process to come when I start attempting it.<br>
<br>
Software delays in C on the MSP430 should be simple using the code provided by the instructor.  By using the C macro __delay_cycles(num_of_cycles), I should be able to use the exact number of cycles I calculated in lab03 with no side effects.<br>

### Software Flow Chart / Algorithms

[LCDDriver](https://github.com/KevinCooper/LCDDriver/)<br>
[clock](https://github.com/KevinCooper/clock/)

### Hardware Schematic

N/A

## Implementation

Please check the clock.h and LCDdriver.h for the documentationas to how each method was implemented.  Check either the lab04 repository or the repositories for either of the drivers.

## Testing Methodology / Results

After the significant bug was found at the beginning of the code, each method was tested as it was implemented.  The main functions being the three write functions, since those utilized the helpers such as moveCursor functions.  The writeCharatcer() was tested by using the characters 'A' and 'B'.  The writeString was verified by using the test case "ABCDEFG12345678" and correctly displayed the letters on the top and numbers on the bottom.  The scrollingLines was tested with two strings longer than 8 characters.  This successfully worked on the second try, with only a simple pointer error on the first try.

## Observations
My driver was successfully able to meet all the requirements for basic, B, and A functionality.  For the most part, porting over the assembly code to C was relatively simple.  However, an error on one line of my code caused an hour of bug hunting and frustration.  The LCD driver is initalized by using the LCDinti and initSPI.  After it is set up, there are several manual functions that may be used, but the three functions that should be used are the writeCharacter, writeLine, and scrollLine functions.  The last two utilize the write character to place the strings provided onto the screen of the MSP430.  However, if you were to use the writeLine with mroe than sixteen character, the characters after the sixteenth one would be left off.  This is not true for the scrollLine, which can handle strings as long as the memory of the MSP430 allows.  Other than the those three methods, the other methods are direct ports from assembly to C.
<br>
##Conclusions
Everything in this project was relatively easy, except for the one bug mentioned in the analysis.  After the screen was able to be blanked by correctly implemented the write4() function, every other method was able to be implemented without much revision needed.  I feel that the writeLine() could be implemented to allow for it to possibly take in two strings instead of one, so more control can be had over what line it is writing to.

## Documentation<br>
None


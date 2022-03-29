/* File Name: colours.h
 * File Description: Header file for colours.c that acts like an interface so that other files can use it's functionality.
 * Student Name: Greg Shalay
 * UoG: 1096689
 */

# ifndef _COLOURS_H // Prevents duplicate linking and compiling errors if this file has already been loaded.
    
    #define _COLOURS_H
    #include <stdio.h>

    void setRedPrint();
    void setYellowPrint();
    void setBlackPrint();
    void setGreenPrint();
    void setBluePrint();
    void setPurplePrint();
    void setCyanPrint();
    void setWhitePrint();
    void resetPrintColour();

#endif
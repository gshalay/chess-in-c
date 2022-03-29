/* File Name: colours.c
 * File Description: Header file for colours.c that acts like an interface so that other files can use it's functionality.
 * Student Name: Greg Shalay
 * UoG: 1096689
 */

#include "colours.h"

void setRedPrint(){
    printf("\033[1;31m");
}

void setBlackPrint(){
    printf("\033[0;30m");
}

void setGreenPrint(){
    printf("\033[0;32m");
}

void setYellowPrint(){
    printf("\033[1;33m");
}

void setBluePrint(){
    printf("\033[0;34m");
}

void setPurplePrint(){
    printf("\033[0;35m");
}

void setCyanPrint(){
    printf("\033[0;36m");
}

void setWhitePrint(){
    printf("\033[0;37m");
}

void resetPrintColour(){
    printf("\033[0m");
}

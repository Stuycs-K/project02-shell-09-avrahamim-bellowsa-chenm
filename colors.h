//Escape codes coppied from https://espterm.github.io/docs/VT100%20escape%20codes.html 

#ifndef COLORS_H
#define COLORS_H

#define RED "\e[31m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define BLINK "\e[5m"
#define BLINKEND ""
#define COLOREND "\e[0m"


#define CLEARLINE "\e[2K"
#define CURSERLEFT "\e[<1>A"
#define CURSERRIGHT "\eD"

#endif

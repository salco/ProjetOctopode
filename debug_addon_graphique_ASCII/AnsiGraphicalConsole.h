#ifndef ANSIGRAPHICALCONSOLE_H
#define ANSIGRAPHICALCONSOLE_H
/** @file AnsiGraphicalConsole.h */
//#define CONSOLE_DELAY_TEST

#ifdef CONSOLE_DELAY_TEST
    #include "mbed.h"
#endif
#define BUFFER_LIMIT 50
void createSLbox(int posX, int posY, int height, int width,const char* title=0);

void createDLbox(int posX, int posY, int height, int width,const char* title=0);

void setText(int posX, int posY,const char* title);

//voir un moyen de patcher les case coller
#endif
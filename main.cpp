//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

#include "mbed.h"
//#include "OSNAPprotocoleDefine.h"
//#include "mouvement.h"
#include "debug.h"
#include "settingDebug.h"
#include "AnsiGraphicalConsole.h"

#include "source/Task/TTaskCritique.h"
#include "source/Task/TTaskAlerte.h"
#include "source/Task/TTaskGeneral.h"


//#include <fcntl.h>
//#include <io.h>
//#include <stdio.h>
//#include <iostream>

DigitalOut myled(LED1, 0);
DigitalIn mybutton(USER_BUTTON);
DigitalOut pinA(PA_13);
DigitalOut pinB(PA_14);

int main()
{
wait(3);
//////////
// Boot //
//////////

    #ifdef DBG_MAIN_INIT
    debug("\n\rInit taskCritique ...");
    #endif
     TTaskCritique taskCritique(40);
    #ifdef DBG_MAIN_INIT 
    debug(" end");
    #endif
    
    //#ifdef DBG_MAIN_INIT
    //debug("\n\rInit taskAlerte ...");
    //#endif
    // TTaskCritique taskAlerte(20);// un-use because i dont know what to do with.
    //#ifdef DBG_MAIN_INIT 
    //debug(" end");
    //#endif
    
    #ifdef DBG_MAIN_INIT
    debug("\n\rInit taskGeneral ...");
    #endif
     TTaskCritique taskGeneral(20);
    #ifdef DBG_MAIN_INIT 
    debug(" end");
    #endif
    
    #ifdef DEBUG_BOOT_GRAPHICAL_INTERFACE
    wait(2);
    debug("\x1B[2J"); //clear screen
    debug("\x1B[25l");//hide cursor
    debug("\x1B[;H"); //cursor default position
    
    //createSLbox(0,0,5,15,"Mode");
    createDLbox(0,0,5,15,"Mode");//(1,12,10,20,"test2");
    createDLbox(16,0,5,15,"Stage");
    //debug("\u00BF \u00BF \u00BF");
    //debug("╔═══╦════╗");
    #endif

    while(1) {

        #if taskCritique
        taskCritique.exec();
        #endif
        
        #if taskAlerte
        taskAlerte.exec();
        #endif
        
        #if taskGeneral
        taskGeneral.exec();
        #endif
        
        /*if (mybutton == 0) { // Button is pressed
            debug("Hello debug world");
            wait(2);
            
            myled = !myled;
            wait(1);
        }*/

    }
    
}
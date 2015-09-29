/**
* @file main.cpp
* @brief Formulaire principal du programme contact
* @author Alexandre Salconi-Denis
* @version 3.01
* @date 06 mars 2014
*
* @mainpage
* <b>Programme de sauvgarde de contact<br></b>
* <em>Modifier par l'utilisation de Classe et d'operateur</em>
* @author Alexandre Salconi-Denis
* @section MainSection1 Description
*
*
*
* - <b>Version</b> : 3.01
*/
  
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
    
    #ifdef ENABLE_TASK_CRIT
        #ifdef DBG_MAIN_INIT
        debug("\n\rInit taskCritique ...");
        #endif
            TTaskCritique taskCritique(40);
        #ifdef DBG_MAIN_INIT 
        debug(" end taskCritique");
        #endif
    #endif
    
    #ifdef ENABLE_TASK_ALERT
        #ifdef DBG_MAIN_INIT
        debug("\n\rInit taskAlerte ...");
        #endif
            TTaskAlerte taskAlerte(20);// un-use because i dont know what to do with.
        #ifdef DBG_MAIN_INIT 
        debug(" end taskAlerte");
        #endif
    #endif
    
    #ifdef ENABLE_TASK_GEN
        #ifdef DBG_MAIN_INIT
        debug("\n\rInit taskGeneral ...");
        #endif
            TTaskGeneral taskGeneral(2/*0*/);
        #ifdef DBG_MAIN_INIT 
        debug(" end taskGeneral");
        #endif
    #endif
    
    

    while(1) {
     
        
        #ifdef ENABLE_TASK_CRIT
            #ifdef DBG_MAIN_FLAG
            debug("\n\r IN taskCritique");
            #endif
        
            taskCritique.exec();
        
            #ifdef DBG_MAIN_FLAG
            debug("  Out taskCritique");
            #endif
        #endif
        
        #ifdef ENABLE_TASK_ALERT
            #ifdef DBG_MAIN_FLAG
            debug("\n\r IN taskAlerte");
            #endif
            
            taskAlerte.exec();
        
            #ifdef DBG_MAIN_FLAG
            debug("  Out taskAlerte");
            #endif        
        #endif
        
        #ifdef ENABLE_TASK_GEN
            #ifdef DBG_MAIN_FLAG
            debug("\n\r IN taskGeneral");
            #endif
            
            taskGeneral.exec();

            #ifdef DBG_MAIN_FLAG
            debug("  Out taskGeneral");
            
            #endif
            
            #ifdef DBG_MAIN_DELAY_SEC
            debug("\n\r\n TICK \n\r\n");
            wait(DBG_MAIN_DELAY_SEC);
            #endif          
        #endif
        
        /*if (mybutton == 0) { // Button is pressed
            debug("Hello debug world");
            wait(2);
            
            myled = !myled;
            wait(1);
        }*/

    }
    
}
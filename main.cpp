
#include "mbed.h"
//#include "OSNAPprotocoleDefine.h"
//#include "mouvement.h"
#include "debug.h"

#include "source/Task/TTaskCritique.h"
#include "source/Task/TTaskAlerte.h"
#include "source/Task/TTaskGeneral.h"


//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------



DigitalOut myled(LED1, 0);
//char str [80];
DigitalIn mybutton(USER_BUTTON);
DigitalOut pinA(PA_13);
DigitalOut pinB(PA_14);

//Serial pc(PB_10,PB_11);


int main()
{
    //  int i = 1;

    //pc.printf("Hello World !\n");
    //pc.scanf ("%79s",str);
    //         string test="allo";
    //    pc.printf(test.c_str());
wait(3);
     TTaskCritique taskCritique(40);
    // TTaskAlerte taskAlerte(20);
     TTaskGeneral  taskGeneral(20);//40);

//////////
// Boot //
//////////

    while(1) {


        taskGeneral.exec();
        //taskAlerte.exec();
        //taskGeneral.exec();
        if (mybutton == 0) { // Button is pressed
            //debug("Hello debug world");
            //taskCritique.exec();
            //wait(2);
            
            /*if(myled) {
                pinB=0;
                pinA=1;
                
            } else {
                pinA=0;
                pinB=1;
            }*/
            myled = !myled;
            wait(1);
        }
        //wait(1);
    }

    /*if(taskCritt)
        delete taskCritt;
    if(taskAlert)
        delete taskAlert;
    if(taskGeneral)
        delete taskGeneral;*/
}

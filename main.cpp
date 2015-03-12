
#include "mbed.h"
//#include "mouvement.h"

//#include "Concience/InstinctPrimaire.h"
#include "source/Task/TTaskCritt.h"
#include "source/Task/TTaskAlert.h"
#include "source/Task/TTaskGen.h"


//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------



DigitalOut myled(LED1);
//char str [80];

int main()
{
    //  int i = 1;

    //pc.printf("Hello World !\n");
    //pc.scanf ("%79s",str);
    //         string test="allo";
    //    pc.printf(test.c_str());

    TTaskCritt *taskCritt = new TTaskCritt(10);
    TTaskAlert *taskAlert = new TTaskAlert(20);
    TTaskGen   *taskGen   = new TTaskGen(40);
//////////
// Boot //
//////////


    while(1) {
        

        taskCritt->exec();
        taskAlert->exec();
        taskGen->exec();




        myled = !myled;
    }
    
    if(taskCritt)
        delete taskCritt;
    if(taskAlert)
        delete taskAlert;
    if(taskGen)
        delete taskGen;
}

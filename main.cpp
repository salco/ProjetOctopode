
#include "mbed.h"
//#include "OSNAPprotocoleDefine.h"
//#include "mouvement.h"
#include "debug.h"
//#include "Concience/InstinctPrimaire.h"
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
Serial patate (PB_6, PA_10);
//Serial pc(PB_10,PB_11);

UART_HandleTypeDef huart3;
void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart3);

}

int main()
{
    //  int i = 1;

    //pc.printf("Hello World !\n");
    //pc.scanf ("%79s",str);
    //         string test="allo";
    //    pc.printf(test.c_str());

    //TTaskCritique taskCritique(1);
    // TTaskAlerte taskAlerte(20);
    // TTaskGeneral  taskGeneral(1);//40);
//////////
// Boot //
//////////

 MX_USART3_UART_Init();
 uint8_t pat[5]= {'A','l','l','o',0};
    while(1) {
    HAL_UART_Transmit(&huart3,pat,5,5);


        //taskAlerte.exec();
        //taskGeneral.exec();
        if (mybutton == 0) { // Button is pressed
            //debug("Hello debug world");
            //taskCritique.exec();
            patate.putc(64);
            
            
            //taskGeneral.exec();
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
    if(taskGen)
        delete taskGen;*/
}

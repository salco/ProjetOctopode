#include "AnsiGraphicalConsole.h"
#include "debug.h"

void createSLbox(int posX, int posY, int height, int width,const char* title)
{
    //PATCH
    posX++;
    posY++;
    //
    
    
    debug("\x1B[%i;%iH",posY,posX);
    debug("\u00DA");//┌
    for(int i=0; i <= (width-2); i++) debug("\u00C4");//─
    debug("\u00BF");//┐
    
    #ifdef CONSOLE_DELAY_TEST
    wait(5);
    #endif
    
    if(title != 0)
    {
        char buffer[10];
        int leight=  sprintf(buffer,"%s",title);
            
        debug("\x1B[%i;%iH",posY+2,posX);
            debug("\u00C3");//├
        for(int i=0; i <= (leight+2); i++) debug("\u00C4");//─   
            debug("\u00D9");//┘
            
        debug("\x1B[%i;%iH",posY,posX+2+leight+2);
            debug("\u00C2");//┬
         debug("\x1B[%i;%iH",posY+1,posX+2+leight+2);
            debug("\u00B3");//│
                
        if(leight < width) // si le nom est plus petit que la box tu lafiche 
        {
         debug("\x1B[%i;%iH",posY+1,posX+2);
         debug(1,"%s",title);//1 est la pour patcher le multiple instance problem 
        }
    }
    
    #ifdef CONSOLE_DELAY_TEST
    wait(5);
    #endif
           
    for(int i = 1;i <= (height-2);i++){
    debug("\x1B[%i;%iH",posY+i,posX);//debug("\x1B[%i;%iH",posX,posY+i);
            debug("\u00B3");//│
        debug("\x1B[%i;%iH",posY+i,posX+width);//debug("\x1B[%i;%iH",posX+width,posY+i);
            debug("\u00B3");//│
            
    #ifdef CONSOLE_DELAY_TEST
    wait(5);
    #endif
    
    }
    
    if(title != 0)
    {        
        debug("\x1B[%i;%iH",posY+2,posX);
            debug("\u00C3");//├
    }
    
    #ifdef CONSOLE_DELAY_TEST
    wait(5);
    #endif
    
    
    debug("\x1B[%i;%iH",posY+(height-1),posX);
        debug("\u00C0");//└
        for(int i=0; i<=width-2; i++)debug("\u00C4");//─
        debug("\u00D9");//┘
        
}

void createDLbox(int posX, int posY, int height, int width,const char* title)
{
    //PATCH
    posX++;
    posY++;
    //
    
    
    debug("\x1B[%i;%iH",posY,posX);
    debug("\u00C9");//╔
    for(int i=0; i <= (width-2); i++) debug("\u00CD");//═ 
    debug("\u00BB");//╗
    
    #ifdef CONSOLE_DELAY_TEST
    wait(5);
    #endif
    
    if(title != 0)
    {
        char buffer[10];
        int leight=  sprintf(buffer,"%s",title);
            
        debug("\x1B[%i;%iH",posY+2,posX);
            debug("\u00CC");//╠
        for(int i=0; i <= (leight+2); i++) debug("\u00CD");//═   
            debug("\u00BC");//╝
            
        debug("\x1B[%i;%iH",posY,posX+2+leight+2);
            debug("\u00CB");//╦
         debug("\x1B[%i;%iH",posY+1,posX+2+leight+2);
            debug("\u00BA");//║
                
        if(leight < width) // si le nom est plus petit que la box tu lafiche 
        {
         debug("\x1B[%i;%iH",posY+1,posX+2);
         debug(1,"%s",title);//1 est la pour patcher le multiple instance problem 
        }
    }
    
    #ifdef CONSOLE_DELAY_TEST
    wait(5);
    #endif
           
    for(int i = 1;i <= (height-2);i++){
    debug("\x1B[%i;%iH",posY+i,posX);//debug("\x1B[%i;%iH",posX,posY+i);
            debug("\u00BA");//║
        debug("\x1B[%i;%iH",posY+i,posX+width);//debug("\x1B[%i;%iH",posX+width,posY+i);
            debug("\u00BA");//║
            
    #ifdef CONSOLE_DELAY_TEST
    wait(5);
    #endif
    
    }
    
    if(title != 0)
    {        
        debug("\x1B[%i;%iH",posY+2,posX);
            debug("\u00CC");//╠
    }
    
    #ifdef CONSOLE_DELAY_TEST
    wait(5);
    #endif
    
    
    debug("\x1B[%i;%iH",posY+(height-1),posX);
        debug("\u00C8");//╚
        for(int i=0; i<=width-2; i++)debug("\u00CD");//═ 
        debug("\u00BC");//╝
        
}

void setText(int posX, int posY,const char* title)
{
    //PATCH
    posX++;
    posY++;
    //
    debug("\x1B[%i;%iH",posY,posX);
    debug(title);
    
}
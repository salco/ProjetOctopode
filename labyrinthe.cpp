/**
  * @file       labyrinthe.cpp
  * @brief      Regroupement de fonction pour enregistrer le millieu en 2D.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#include "labyrinthe.h"


Labyrinthe::Labyrinthe()
{
    direction=0;
    mapDuLabyrinthe.clear();
    addMap(0,0);
    m_posX=0;
    m_posY=0;
}

Labyrinthe::~Labyrinthe()
{
}

char Labyrinthe::getCoordoner(char &x, char &y)
{
    char result;
    char newPosX,newPosY;
    newPosX = 3*(x/3); // je veux le nobre de fois quil a fait un tours et donc seulment les entier
    newPosY = 3*(y/3);

    x = newPosX;
    y = newPosY;
    
    result = 2 + newPosX;

    switch(newPosY) {
        case-1:
            result = result + (3*2);
            break;

        case 0:
            result = result + (3*1);
            break;

        case 1:
            result = result + (3*0);
            break;
    }

    debug(DEBUGLABCOORD,"\n\r result: X: %02d   Y:%02d",newPosX,newPosY);
    debug(DEBUGLABCOORD,"\n\r result: :%02d \n\r",result);

    return result;
}
char Labyrinthe::getCoordoner(void)
{
    char result=0;
    char newPosX,newPosY;

    newPosX = 3*(m_posX/3); // je veux le nobre de fois quil a fait un tours et donc seulment les entier
    newPosY = 3*(m_posY/3);

    newPosX = m_posX-newPosX;
    newPosY = m_posY-newPosY;

    result = 2 + newPosX;

    switch(newPosY) {
        case-1:
            result = result + (3*2);
            break;

        case 0:
            result = result + (3*1);
            break;

        case 1:
            result = result + (3*0);
            break;
    }

    debug(DEBUGLABCOORD,"\n\r result: X: %02d   Y:%02d",newPosX,newPosY);
    debug(DEBUGLABCOORD,"\n\r result: :%02d \n\r",result);

    return result;
}

string Labyrinthe::showMap(void) 
{
    return showMap(m_posX,m_posY);
}
string Labyrinthe::showMap(char x, char y)
{
    //bool result=false;
    string theMap;
    theMap.clear();
    /* char newPosX = x;
     char newPosY = y;

     getCoordoner(newPosX,newPosY);
     unsigned char templateX,templateY;
     for(int i=0; ((i*DEFAULTLABLEIGHT)<mapDuLabyrinthe.size()) && (!result);i++)
     {
        templateX = (mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)])>>1;
        templateY = ((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)])&1)<<7;
        templateY += ((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)+1])>>2);

        if((templateX == newPosX) && (templateY == newPosY))
        {
            result=true;
            theMap.append(1,((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)+1])& 3));
            }
     }*/
    int stringPosition = searchCoord(x,y);
    if(stringPosition != -1) {
        theMap.append(1,((mapDuLabyrinthe[(stringPosition)+1]>>0)& 3));
        theMap.append(1,((mapDuLabyrinthe[(stringPosition)+2]>>6)& 3));
        theMap.append(1,((mapDuLabyrinthe[(stringPosition)+2]>>4)& 3));

        theMap.append(1,((mapDuLabyrinthe[(stringPosition)+2]>>2)& 3));
        theMap.append(1,((mapDuLabyrinthe[(stringPosition)+2]>>0)& 3));
        theMap.append(1,((mapDuLabyrinthe[(stringPosition)+3]>>6)& 3));

        theMap.append(1,((mapDuLabyrinthe[(stringPosition)+3]>>4)& 3));
        theMap.append(1,((mapDuLabyrinthe[(stringPosition)+3]>>2)& 3));
        theMap.append(1,((mapDuLabyrinthe[(stringPosition)+3]>>0)& 3));
    }
    
    #ifdef DEBUG_BOOT_GRAPHICAL_INTERFACE
    debug("\n\r----------showmap------\n\r");
    debug(" map size: %i \n\r",mapDuLabyrinthe.size());
    debug("  stringPosition: %i \n\r",stringPosition); 
    if(stringPosition != -1) {
        debug("  (mapDuLabyrinthe[(stringPosition)+1]>>0): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+1]>>0),((mapDuLabyrinthe[(stringPosition)+1]>>0)& 3));
        debug("  (mapDuLabyrinthe[(stringPosition)+2]>>6): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+2]>>6),((mapDuLabyrinthe[(stringPosition)+2]>>6)& 3));
        debug("  (mapDuLabyrinthe[(stringPosition)+2]>>4): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+2]>>4),((mapDuLabyrinthe[(stringPosition)+2]>>4)& 3));
        debug("  \n\r");
        debug("  (mapDuLabyrinthe[(stringPosition)+2]>>2): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+2]>>2),((mapDuLabyrinthe[(stringPosition)+2]>>2)& 3));
        debug("  (mapDuLabyrinthe[(stringPosition)+2]>>0): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+2]>>0),((mapDuLabyrinthe[(stringPosition)+2]>>0)& 3));
        debug("  (mapDuLabyrinthe[(stringPosition)+3]>>6): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+3]>>6),((mapDuLabyrinthe[(stringPosition)+3]>>6)& 3));
        debug("  \n\r");
        debug("  (mapDuLabyrinthe[(stringPosition)+3]>>4): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+3]>>4),((mapDuLabyrinthe[(stringPosition)+3]>>4)& 3));
        debug("  (mapDuLabyrinthe[(stringPosition)+3]>>2): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+3]>>2),((mapDuLabyrinthe[(stringPosition)+3]>>2)& 3));
        debug("  (mapDuLabyrinthe[(stringPosition)+3]>>0): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+3]>>0),((mapDuLabyrinthe[(stringPosition)+3]>>0)& 3));
        debug("  \n\r");
    }
    debug("\n\r----------------------\n\r");
    #endif
    return theMap;
}

bool Labyrinthe::updateMap(string mapUpdated)
{
    return updateMap(mapUpdated,m_posX,m_posY);
}
bool Labyrinthe::updateMap(string mapUpdated,char x, char y)
{
    bool result = true;
    int stringPosition = searchCoord(x,y);

    if(stringPosition == -1)
        result= false;
    else {
        mapDuLabyrinthe[(stringPosition)+1] = ((mapDuLabyrinthe[(stringPosition)+1]) & 0xFC) | ((mapUpdated[0] &0x03)<<0);
        mapDuLabyrinthe[(stringPosition)+2] = ((mapDuLabyrinthe[(stringPosition)+2]) & 0x3F) | ((mapUpdated[1] &0x03)<<6);
        mapDuLabyrinthe[(stringPosition)+2] = ((mapDuLabyrinthe[(stringPosition)+2]) & 0xCF) | ((mapUpdated[2] &0x03)<<4);

        mapDuLabyrinthe[(stringPosition)+2] = ((mapDuLabyrinthe[(stringPosition)+2]) & 0xF3) | ((mapUpdated[3] &0x03)<<2);
        mapDuLabyrinthe[(stringPosition)+2] = ((mapDuLabyrinthe[(stringPosition)+2]) & 0xFC) | ((mapUpdated[4] &0x03)<<0);
        mapDuLabyrinthe[(stringPosition)+2] = ((mapDuLabyrinthe[(stringPosition)+3]) & 0x3F) | ((mapUpdated[5] &0x03)<<6);

        mapDuLabyrinthe[(stringPosition)+2] = ((mapDuLabyrinthe[(stringPosition)+2]) & 0xCF) | ((mapUpdated[6] &0x03)<<4);
        mapDuLabyrinthe[(stringPosition)+2] = ((mapDuLabyrinthe[(stringPosition)+2]) & 0xF3) | ((mapUpdated[7] &0x03)<<2);
        mapDuLabyrinthe[(stringPosition)+2] = ((mapDuLabyrinthe[(stringPosition)+2]) & 0xFC) | ((mapUpdated[8] &0x03)<<0);
    }


    return result;
}
bool Labyrinthe::addMap(char x, char y)
{
    bool result = true;
    x &= 0x7F; // on coupe le 8eme bit
    y &= 0x7F; //

    mapDuLabyrinthe.append(1,((x<<1) | (y>>6)) );//x7,x6,x5,x4,x3,x2,x1,y7
    mapDuLabyrinthe.append(1,y<<1);              //y6,y5,y4,y3,y2,y1,[C1],[C1]
    mapDuLabyrinthe.append(2,0);                 //add C2-C9 vide
    
    #ifdef DEBUG_LABYRINTHE_ADD_MAP
    debug("----addMap----\n\r");
    debug("x = %i \n\r",x);
    debug("y = %i \n\r",y);
    debug("((x<<1) | (y>>6)) = %i \n\r",((x<<1) | (y>>6)));
    debug("-------------\n\r");
    #endif

    return result;
}

int Labyrinthe::searchCoord(char posX,char posY)
{
    bool result=false;
    //string theMap;
    //theMap.clear();
    debug(DEBUGLABSEARCHCOORD,"------Search coord------");
    debug(DEBUGLABSEARCHCOORD," posX: %i posY: %i \n\r",posX,posY);
    
    char newPosX = posX;
    char newPosY = posY;

    getCoordoner(newPosX,newPosY);
    debug(DEBUGLABSEARCHCOORD," new posX: %i new posY: %i \n\r",newPosX,newPosY);
    unsigned char templateX,templateY;
    int i=0;
    debug(DEBUGLABSEARCHCOORD," map size: %i \n\r",mapDuLabyrinthe.size());
    for( ; ((i*DEFAULTLABLEIGHT) < mapDuLabyrinthe.size()) && (!result); i++) {
       
        templateX = (mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)])>>1;
        templateY = ((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)])&1)<<7;
        templateY += ((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)+1])>>2);

        if((templateX == newPosX) && (templateY == newPosY)) {
            result=true;
            //theMap.append(1,((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)+1])& 3));
        }
    }
    debug(DEBUGLABSEARCHCOORD," templateX: %i \n\r",templateX);
    debug(DEBUGLABSEARCHCOORD," templateY: %i \n\r",templateY);
    debug(DEBUGLABSEARCHCOORD,"--------------------");
    return (i==0? -1:i*DEFAULTLABLEIGHT);
}

char Labyrinthe::getC(char cX)
{
 return  getC(m_posX, m_posY, cX);
}
char Labyrinthe::getC(char x, char y)
{
    char newPosX = x;
    char newPosY = y;
    char maCoordoner;
    maCoordoner=getCoordoner(newPosX,newPosY);
    
 return  getC(x, y, maCoordoner);
}
char Labyrinthe::getC(char x, char y, char cX)
{
    char myCoordoner = 0xFF;
    string result = showMap(x,y);
    if(result.size() != 0) {
        myCoordoner= result[cX];
    }
    return myCoordoner;
}
void Labyrinthe::setC(char value, char x, char y, char cX)
{
    string result = showMap(x,y);
    if(result.size() != 0) {
        result[cX]=value;
        updateMap(result,x,y);
    }
}
void Labyrinthe::setC(char value, char cX)
{
    setC(value,m_posX, m_posY,cX);
}
void Labyrinthe::setC(char value, char x, char y)
{
    char newPosX = x;
    char newPosY = y;
    char maCoordoner;
    maCoordoner=getCoordoner(newPosX,newPosY);
    
    setC(value,x,y,maCoordoner);
}
void Labyrinthe::setC_Up(char value)
{
    setC(value,m_posX, m_posY+1);
}
void Labyrinthe::setC_Down(char value)
{
    setC(value,m_posX, m_posY-1);
}
void Labyrinthe::setC_Left(char value)
{
    setC(value,m_posX-1, m_posY);
}
void Labyrinthe::setC_Right(char value)
{
    setC(value,m_posX+1, m_posY);
}
void Labyrinthe::setMyPos(char value)
{
    setC(value, m_posX, m_posY);
}
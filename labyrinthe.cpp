/**
  * @file       labyrinthe.cpp
  * @brief      Regroupement de fonction pour enregistrer le millieu en 2D.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#include "labyrinthe.h"

typedef Labyrinthe::coordoner_t coordonerr;
typedef Labyrinthe::case_t case_t;

Labyrinthe::Labyrinthe()
{
    direction=0;
    mapDuLabyrinthe.clear();
    addMap(0,0);
    m_posX=1;
    m_posY=1;
}

Labyrinthe::~Labyrinthe()
{
}

coordonerr Labyrinthe::getCoordoner(char &x, char &y)
{
    coordonerr result = unset;
    char newPosX,newPosY;
    
    #ifdef DEGUG_LABIRINTH_GET_COORDONER
    debug("\n\r----------getCoordoner------\n\r");
    debug(" x: %i Y: %i\n\r",x,y);
    #endif
    
        
    newPosX = 3*((((signed)x<0)? x-2:x)/3); // je veux le nobre de fois quil a fait un tours et donc seulment les entier
    newPosY = 3*((((signed)y<0)? y-2:y)/3);
    
    #ifdef DEGUG_LABIRINTH_GET_COORDONER
    debug(" newPosX: %i newPosY: %i\n\r",newPosX,newPosY);
    #endif

    
    
    switch(x - newPosX){
        case 0:
            switch(y - newPosY){
                case 0:
                    result=C1;
                    break;
                
                case 1:
                    result=C2;
                    break;
                
                case 2:
                    result=C3;
                    break;
                }
        break;
        
        case 1:
            switch(y - newPosY){
                case 0:
                    result=C4;
                    break;
                
                case 1:
                    result=C5;
                    break;
                
                case 2:
                    result=C6;
                    break;
                }
        break;
        
        case 2:
            switch(y - newPosY){
                case 0:
                    result=C7;
                    break;
                
                case 1:
                    result=C8;
                    break;
                
                case 2:
                    result=C9;
                    break;
                }
        break;       
        }
    
    x = newPosX;
    y = newPosY;
    /*result =(coordonerr)( 2 + newPosX);

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
    }*/
    #ifdef DEGUG_LABIRINTH_GET_COORDONER
    debug(" newPosX: %i newPosY: %i\n\r",newPosX,newPosY);
    //debug("\n\r result: X: %02d   Y:%02d",newPosX,newPosY);
    debug("\n\r result: :%02d \n\r",result);
    debug("\n\r--------------------\n\r");
    #endif

    return result;
}
coordonerr Labyrinthe::getCoordoner(void)
{
    coordonerr result;
    char newPosX = m_posX;
    char newPosY = m_posY;
    
    result = getCoordoner(newPosX,newPosY);

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
        debug("  (mapDuLabyrinthe[(stringPosition)+1]>>0): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+1]>>0),((mapDuLabyrinthe[(stringPosition)+1]>>0)& 3)); //c1
        debug("  (mapDuLabyrinthe[(stringPosition)+2]>>6): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+2]>>6),((mapDuLabyrinthe[(stringPosition)+2]>>6)& 3)); //c2
        debug("  (mapDuLabyrinthe[(stringPosition)+2]>>4): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+2]>>4),((mapDuLabyrinthe[(stringPosition)+2]>>4)& 3)); //c3
        debug("  \n\r");
        debug("  (mapDuLabyrinthe[(stringPosition)+2]>>2): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+2]>>2),((mapDuLabyrinthe[(stringPosition)+2]>>2)& 3)); //c4
        debug("  (mapDuLabyrinthe[(stringPosition)+2]>>0): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+2]>>0),((mapDuLabyrinthe[(stringPosition)+2]>>0)& 3)); //c5
        debug("  (mapDuLabyrinthe[(stringPosition)+3]>>6): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+3]>>6),((mapDuLabyrinthe[(stringPosition)+3]>>6)& 3)); //c6
        debug("  \n\r");
        debug("  (mapDuLabyrinthe[(stringPosition)+3]>>4): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+3]>>4),((mapDuLabyrinthe[(stringPosition)+3]>>4)& 3)); //c7
        debug("  (mapDuLabyrinthe[(stringPosition)+3]>>2): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+3]>>2),((mapDuLabyrinthe[(stringPosition)+3]>>2)& 3)); //c8
        debug("  (mapDuLabyrinthe[(stringPosition)+3]>>0): %i &3== %i  \n\r",(mapDuLabyrinthe[(stringPosition)+3]>>0),((mapDuLabyrinthe[(stringPosition)+3]>>0)& 3)); //c9
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

//renvoi l'ID du 4 byte de la tuile dans le string
int Labyrinthe::searchCoord(char posX,char posY)
{
    bool result=false;
    char newPosX = posX;
    char newPosY = posY;
    unsigned char templateX = 0;
    unsigned char templateY = 0;
    int i=0;
    //string theMap;
    //theMap.clear();
    debug(DEBUGLABSEARCHCOORD,"------Search coord------");
    debug(DEBUGLABSEARCHCOORD," posX: %i posY: %i \n\r",posX,posY);
    
    
    getCoordoner(newPosX,newPosY);
    debug(DEBUGLABSEARCHCOORD," new posX: %i new posY: %i \n\r",newPosX,newPosY);
    
    debug(DEBUGLABSEARCHCOORD," map size: %i \n\r",mapDuLabyrinthe.size());
    
    for( ; ((i*DEFAULTLABLEIGHT) < mapDuLabyrinthe.size()) && (!result); i++) {
       
        templateX = (mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)])>>1;
        templateY = (((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)])&1)<<7) | ((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)+1])>>2);
        //templateY += ((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)+1])>>2);

        if((templateX == newPosX) && (templateY == newPosY)) {
            result=true;
            //theMap.append(1,((mapDuLabyrinthe[(i*DEFAULTLABLEIGHT)+1])& 3));
        }
    }
    i--;
    debug(DEBUGLABSEARCHCOORD," templateX: %i \n\r",templateX);
    debug(DEBUGLABSEARCHCOORD," templateY: %i \n\r",templateY);
    debug(DEBUGLABSEARCHCOORD," result: %i \n\r",result?1:0);
    debug(DEBUGLABSEARCHCOORD," i*DEFAULTLABLEIGHT: %i \n\r",i*DEFAULTLABLEIGHT); 
    debug(DEBUGLABSEARCHCOORD,"--------------------");
    return (result==false? -1:i*DEFAULTLABLEIGHT);
}

case_t Labyrinthe::getC(coordonerr cX)
{
 return  getC(m_posX, m_posY, cX);
}
/**
* @param x position X.
* @param y position Y.
* @return 
*/
case_t Labyrinthe::getC(char x, char y)
{
    char newPosX = x;
    char newPosY = y;
    coordonerr maCoordoner;
    maCoordoner=getCoordoner(newPosX,newPosY);
    
 return  getC(x, y, maCoordoner);
}

case_t Labyrinthe::getC(char x, char y, coordonerr cX)
{
    char myCoordoner = 0xFF;
    string result = showMap(x,y);
    if(result.size() != 0) {
        myCoordoner= result[cX];
    }
    return (case_t)myCoordoner;
}
void Labyrinthe::setC(case_t value, char x, char y, coordonerr cX)
{
    #ifdef DEGUG_LABIRINTH_SET_COORDONER
        debug("------SetC coord------");
        #endif
    string result = showMap(x,y);
    if(result.size() != 0) {
        result[cX-1]=value;
        
        
        #ifdef DEGUG_LABIRINTH_SET_COORDONER
        debug("\n\r  Labyrinthe map: X:%02x Y:%02x \n\r",x,y);
        debug("value: %i\n\r",value);
        debug("coordoner: %i\n\r",cX);
        for(int i=0; i<3; i++) debug(" [%02X] ",result[i+6]);
        debug("\n\r");
        for(int i=0; i<3; i++) debug(" [%02X] ",result[i+3]);
        debug("\n\r");
        for(int i=0; i<3; i++) debug(" [%02X] ",result[i]);
        debug("\n\r");
        #endif
        
    updateMap(result,x,y);
        
        #ifdef DEGUG_LABIRINTH_SET_COORDONER
        debug("---------------------");
        #endif
    }
}
void Labyrinthe::setC(case_t value, coordonerr cX)
{
    setC(value,m_posX, m_posY,cX);
}
void Labyrinthe::setC(case_t value, char x, char y)
{
    char newPosX = x;
    char newPosY = y;
    coordonerr maCoordoner;
    maCoordoner=getCoordoner(newPosX,newPosY);
    
    setC(value,x,y,maCoordoner);
}
void Labyrinthe::setC_Up(case_t value)
{
    setC(value,m_posX, m_posY+1);
}
void Labyrinthe::setC_Down(case_t value)
{
    setC(value,m_posX, m_posY-1);
}
void Labyrinthe::setC_Left(case_t value)
{
    setC(value,m_posX-1, m_posY);
}
void Labyrinthe::setC_Right(case_t value)
{
    setC(value,m_posX+1, m_posY);
}
void Labyrinthe::setMyPos(case_t value)
{
    setC(value, m_posX, m_posY);
}
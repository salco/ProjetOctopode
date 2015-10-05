/**
  * @file       labyrinthe.h
  * @brief      Regroupement de fonction pour enregistrer le millieu en 2D.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef LABYRINTHE_H
#define LABYRINTHE_H
  
#define DEFAULTLABLEIGHT 4
#define DEBUGLABCOORD 0
#define DEBUGLABSEARCHCOORD 0

#include "mbed.h"
#include "debug.h"
#include "settingDebug.h"
#include <string>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


/*#define VIDE 3
#define EXPLORER 1
#define MUR 2
#define PAS_EXPLORER 0*/

// 1 tuile == 4 byte


    
class Labyrinthe
{
signed char m_posX,m_posY;
char direction;
string mapDuLabyrinthe;



public:
enum coordoner_t{
/* C7,C8,C9 */
/* C4,C5,C6 */
/* C1,C2,C3 */
    unset = -1,
    C1 = 1,
    C2 = 2,
    C3 = 3,
    C4 = 4,
    C5 = 5,
    C6 = 6,
    C7 = 7,
    C8 = 8,
    C9 = 9
    };
    
    enum case_t{
        error       =-1,
        pasExplorer = 0,
        explorer    = 1,
        mur         = 2,
        vide        = 3
    };
    
Labyrinthe();
~Labyrinthe();

char getDirection(){return direction;}
void setDirection(char dir){direction= dir;}

signed char getX(void){return m_posX;}
void setX(signed char x){m_posX = x;}

signed char getY(void){return m_posY;}
void setY(signed char y){m_posY = y;}

void goUp(void){m_posY++;}
void goDown(void){m_posY--;}
void goLeft(void){m_posX--;}
void goRight(void){m_posX++;}

void moveFoward(void){moveFoward(direction);}
void moveFoward(char dir);
void moveBackward(void){moveBackward(direction);}
void moveBackward(char dir);
void moveToLeft(void){moveToLeft(direction);}
void moveToLeft(char dir);
void moveToRight(void){moveToRight(direction);}
void moveToRight(char dir);

void turnBack(void);
void turnLeft(void);
void turnRight(void);

char caseToChar(case_t value);

case_t getC_Foward(void){return getC_Foward(direction);}
case_t getC_Foward(char dir);
case_t getC_Backward(void){return getC_Backward(direction);}
case_t getC_Backward(char dir);
case_t getC_ToLeft(void){return getC_ToLeft(direction);}
case_t getC_ToLeft(char dir);
case_t getC_ToRight(void){return getC_ToRight(direction);}
case_t getC_ToRight(char dir);

case_t getC(coordoner_t cX);
case_t getC(signed char x, signed char y, coordoner_t cX);
case_t getC(signed char x, signed char y);
void setC(case_t value, signed char x, signed char y, coordoner_t cX);
void setC(case_t value, coordoner_t cX);
void setC(case_t value, signed char x, signed char y);

void setC_Up(case_t value);
void setC_Down(case_t value);
void setC_Left(case_t value);
void setC_Right(case_t value);
void setMyPos(case_t value);

      /**
       * Surcharge de showMap(void)
       * @return The formated map 3x3 result
       */
        string showMap(void);
        
      /**
       * Fonction permetant de sortire la map de la position x et y
       * @param x position X.
       * @param y position Y.
       * @return The formated map 3x3 result
       */
        string showMap(signed char x, signed char y);
        string getAllMap(void){return mapDuLabyrinthe;}
        void setAllMap(string updatedMap){mapDuLabyrinthe = updatedMap;}



    private:
    int searchCoord(signed char posX,signed char posY);

    coordoner_t getCoordoner(signed char &x, signed char &y);
    coordoner_t getCoordoner(void);
    
    bool updateMap(string mapUpdated);
    bool updateMap(string mapUpdated,signed char x, signed char y);
    bool addMap(signed char x, signed char y);

};
#endif //LABYRINTHE_H//
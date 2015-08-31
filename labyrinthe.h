/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#define DEFAULTLABLEIGHT 4
#define DEBUGLABCOORD 1

#include "mbed.h"
#include "debug.h"
#include <string>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


#define VIDE 3
#define EXPLORER 1
#define MUR 2
#define PAS_EXPLORER 0

enum coordonerr{
/* C7,C8,C9 */
/* C4,C5,C6 */
/* C1,C2,C3 */

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
    
class Labyrinthe
{
char m_posX,m_posY;
char direction;
string mapDuLabyrinthe;

int searchCoord(char posX,char posY);

public:
Labyrinthe();
~Labyrinthe();

char getDirection(){return direction;}
void setDirection(char dir){direction= dir;}

char getX(void){return m_posX;}
void setX(char x){m_posX = x;}

char getY(void){return m_posY;}
void getY(char y){m_posY = y;}

void goUp(void){m_posY++;}
void goDown(void){m_posY--;}
void goLeft(void){m_posX--;}
void posRight(void){m_posX++;}

char getCoordoner(char &x, char &y);
char getCoordoner(void);

char getC(char cX);
char getC(char x, char y, char cX);
char getC(char x, char y);
void setC(char value, char x, char y, char cX);
void setC(char value, char cX);
void setC(char value, char x, char y);

void setC_Up(char value);
void setC_Down(char value);
void setC_Left(char value);
void setC_Right(char value);

string showMap(void);
string showMap(char x, char y);

bool updateMap(string mapUpdated);
bool updateMap(string mapUpdated,char x, char y);
bool addMap(char x, char y);


};
#endif //LABYRINTHE_H//
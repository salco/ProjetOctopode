/**
  * @file       directive.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef DIRECTIVE_H
#define DIRECTIVE_H


                                    

#define mvToADC(value)((value*1.023)/5)
#define ADCTomv(value)((value*5)/1.023)
#define ultrasonicToInch(value)(ADCTomv(value)/9.8)

#define inchToCm(value)(value*2.54)
#define mvToInch(value)(value/9.8)



#include "mbed.h"
#include "debug.h"
#include "source/Task/TTask.h"
#include "Motrice/mouvement.h"
#include <stdlib.h>     /* srand, rand */
#include <list>
#include <time.h>       /* time */
#include "labyrinthe.h"
#include "settingDebug.h"

    //////////////////////////////
    // 00 - Nothing             //
    //X01 - Calibration(milieu) //
    //X02 - Debout              //
    //X03 - Coucher             //
    //X04 - Tourne Gauche       //
    //X05 - Tourne Droite       //
    // 06 - Marche              //
    // 07 - Recule              //
    // 08 - Repositioner  legs  //
    // 09 - Crabe  Gauche       // Dont use Crabe because it's really anoying
    // 10 - Crabe  Droite       // Dont use Crabe because it's really anoying
    // 11 - Position naturel    //
    //////////////////////////////
    #define TBL_CMD_NOTHING     0
    #define TBL_CMD_CALIBRATION 1
    #define TBL_CMD_DEBOUT      2
    #define TBL_CMD_COUCHER     3
    #define TBL_CMD_TURN_LEFT   4
    #define TBL_CMD_TURN_RIGHT  5
    #define TBL_CMD_MARCHE      6
    #define TBL_CMD_RECULE      7
    #define TBL_CMD_REPOSITIONE 8
    #define TBL_CMD_CRAB_LEFT   9
    #define TBL_CMD_CRAB_RIGHT  10
    #define TBL_CMD_DEFAULT_POS 11
    
class Directive : public TTask
{
    //CtrlBridge* m_CtrlBridge;
    Faculter_motrice *ctrDesPattes;
    /*Serial*//*Raw*/Serial *ssc32;
    string m_capteurUltrasonic,m_capteurIR,m_capteurProximiter;
    //char c;
    Labyrinthe* myMaze;
    bool followThePath;
    
    struct positionXY
    {
        signed char posX;
        signed char posY;
        char direction;
    };
   std::list<positionXY> bufferNewWay;
    
    double m_valueCapteurUltrasonic,m_valueCapteurIR;
    int m_valueCapteurProximiter;
    unsigned char tableauDeCommange[10];
    unsigned char size_tableauDeCommange;
    void updateModuleValue(void);
    void turnRightDirection(char currentDir, char nextDir);
    
    
protected:
/*
    * Tache principale de la classe
    */
    virtual void task(void);
    void analiseMaze(void);
    char checkOtherWay(char dir, bool checkExplorer=false);
    void checkOtherWay(char &caseFront, char &caseBack, char &caseLeft, char &caseRight);
    
    bool searchNewWay(void);
    
        bool isAnotherWay(void);
public:
    Directive();
    virtual~Directive();
    double IRToCm (double miliVolt);
    void addTableauDeCommande(unsigned char value);

};
#endif // DIRECTIVE_H
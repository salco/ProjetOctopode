/**
  * @file       directive.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#define DEBUG_DIRECTIVE_TEST 1
#define DEBUG_DIRECTIVE_LABYRINTH 1
                                    

#define mvToADC(value)((value*1.023)/5)
#define ADCTomv(value)((value*5)/1.023)
#define ultrasonicToInch(value)(ADCTomv(value)/9.8)

#define mvToInch(value)(value/9.8)



#include "mbed.h"
#include "debug.h"
#include "source/Task/TTask.h"
#include "Motrice/mouvement.h"
#include <stdlib.h>     /* srand, rand */
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
class Directive : public TTask
{
    //CtrlBridge* m_CtrlBridge;
    Faculter_motrice *ctrDesPattes;
    /*Serial*//*Raw*/Serial *ssc32;
    string m_capteurUltrasonic,m_capteurIR,m_capteurProximiter;
    //char c;
    Labyrinthe* myMaze;
    
    int m_valueCapteurUltrasonic,m_valueCapteurIR,m_valueCapteurProximiter;
    unsigned char tableauDeCommange[10];
    unsigned char size_tableauDeCommange;
    void updateModuleValue(void);
    
protected:
/*
    * Tache principale de la classe
    */
    virtual void task(void);
    void analiseMaze(void);
public:
    Directive();
    virtual~Directive();
    double IRToCm (double miliVolt);
    void addTableauDeCommande(unsigned char value);

};
#endif // DIRECTIVE_H
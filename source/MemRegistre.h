/**
  * @file       MemRegistre.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef MEMREG_H
#define MEMREG_H


#include "ListChainer.h"

class MemRegistre
{
ListChainer m_moduleActioneur;
int m_positionActioneur;
ListChainer m_moduleCapteur;
int m_positionCapteur;
ListChainer m_moduleMemoire;
int m_positionMemoire;


public:

MemRegistre();
virtual ~MemRegistre();

bool remAllActioneur(void){m_moduleActioneur.remAll();return 1;}
bool remActioneur(int position){m_moduleActioneur.remAtPos(position);return 1;}
bool addActioneur(Module module){m_moduleActioneur.addNode(module);return 1;}
Module firstActioneur(void);
Module nextActioneur(void);
int getSizeActioneur(void){return m_moduleActioneur.getSize();}

bool remAllCapteur(void){m_moduleCapteur.remAll();return 1;}
bool remCapteur(int position){m_moduleCapteur.remAtPos(position);return 1;}
bool addCapteur(Module module){m_moduleCapteur.addNode(module);return 1;}
Module firstCapteur(void);
Module nextCapteur(void);
int getSizeCapteur(void){return m_moduleCapteur.getSize();}

bool remAllMemoire(void){m_moduleMemoire.remAll();return 1;}
bool remMemoire(int position){m_moduleMemoire.remAtPos(position);return 1;}
bool addMemoire(Module module){m_moduleMemoire.addNode(module);return 1;}
Module firstMemoire(void);
Module nextMemoire(void);
int getSizeMemoire(void){return m_moduleMemoire.getSize();}






};
#endif // MEMREG_H //




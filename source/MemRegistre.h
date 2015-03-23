/**
  * @file       MemRegistre.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef MEMREG_H
#define MEMREG_H

#include <list>
#include "Module.h"
//#include "ListChainer.h"

using namespace std;// Or using std::list;

class MemRegistre
{
    list<Module> m_moduleActioneur;//ListChainer m_moduleActioneur;
    list<Module>::iterator m_positionActioneur;//int m_positionActioneur;

    list<Module> m_moduleCapteur;//ListChainer m_moduleCapteur;
    list<Module>::iterator m_positionCapteur;//int m_positionCapteur;

    list<Module> m_moduleMemoire;//ListChainer m_moduleMemoire;
    list<Module>::iterator m_positionMemoire;//int m_positionMemoire;


public:
// pt metre des inline  pour les fonction dans le h

    MemRegistre();
    virtual ~MemRegistre();
    unsigned char getAdressDispo(const unsigned char &startValue);
    bool isAdresseValide(const char &adresse);
    bool isAdresseValide(const char &adresse, Module &m );


    //actioneur//
    bool remAllActioneur(void) {
        m_moduleActioneur.clear();
        return 1;
    }
    inline bool remActioneur(int position) {
        list<Module>::iterator it1=m_moduleActioneur.begin();
        for(char i=position; i>1; i--) it1++;
        m_moduleActioneur.erase(it1);
        return 1;
    }
    bool addActioneur(Module module) {
        m_moduleActioneur.push_back(module);
        return 1;
    }
    Module firstActioneur(void);
    Module nextActioneur(void);
    int getSizeActioneur(void) {
        return m_moduleActioneur.size();
    }
//capteur//
    bool remAllCapteur(void) {
        m_moduleCapteur.clear();
        return 1;
    }
    bool remCapteur(int position) {
        list<Module>::iterator it1=m_moduleCapteur.begin();
        for(char i=position; i>1; i--) it1++;
        m_moduleCapteur.erase(it1);
        return 1;
    }
    bool addCapteur(Module module) {
        m_moduleCapteur.push_back(module);
        return 1;
    }
    Module firstCapteur(void);
    Module nextCapteur(void);
    int getSizeCapteur(void) {
        return m_moduleCapteur.size();
    }
//memoire//
    bool remAllMemoire(void) {
        m_moduleMemoire.clear();
        return 1;
    }
    bool remMemoire(int position) {
        list<Module>::iterator it1=m_moduleMemoire.begin();
        for(char i=position; i>1; i--) it1++;
        m_moduleMemoire.erase(it1);
        return 1;
    }
    bool addMemoire(Module module) {
        m_moduleMemoire.push_back(module);
        return 1;
    }
    Module firstMemoire(void);
    Module nextMemoire(void);
    int getSizeMemoire(void) {
        return m_moduleMemoire.size();
    }

};
#endif // MEMREG_H //




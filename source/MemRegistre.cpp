/*
 * memoireRegistre.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: salco
 */
/**
* @file llistcontact.cpp
* @brief Formulaire de la class LList et node_t
* @author Alexandre Salconi-Denis
* @version 3.01
* @date 06 mars 2014
*/
#include "MemRegistre.h"

MemRegistre::MemRegistre()
{
    m_positionActioneur = m_moduleActioneur.begin();
    m_positionCapteur = m_moduleCapteur.begin();
    m_positionMemoire = m_moduleMemoire.begin();
}
MemRegistre::~MemRegistre()
{
}

unsigned char MemRegistre::getAdressDispo(const unsigned char &startValue)
{
    //list<Module>::iterator it1;
    unsigned char addrDispo=(startValue==0)?1:startValue;

    //Module templateModule;
    for(bool addrFind=false; (addrDispo!=0)&&(!addrFind); addrDispo++) {
        /* addrFind=true;
         for (list<Module>::iterator it=m_moduleActioneur.begin(); it != m_moduleActioneur.end(); ++it)
             if(it->regA == addrDispo) addrFind = false;

         for (std::list<Module>::iterator it=m_moduleCapteur.begin(); it != m_moduleCapteur.end(); ++it)
             if(it->regA == addrDispo) addrFind = false;

         for (std::list<Module>::iterator it=m_moduleMemoire.begin(); it != m_moduleMemoire.end(); ++it)
             if(it->regA == addrDispo) addrFind = false;*/
        addrFind = !isAdresseValide(addrDispo);

        if((addrDispo==255) && (!addrFind))addrDispo=0; //les 255 adresses son utiliser // bravo le robot doit etre under heavy load.
    }

    return addrDispo;
}
bool MemRegistre::isAdresseValide(const char &adresse, Module &m )
{
    list<Module>::iterator it1;
    bool addrFind=false;
    //Module templateModule;
    //for(unsigned char addrDispo=1; (addrDispo!=0)&&(!addrFind); addrDispo++) {

    for (list<Module>::iterator it=m_moduleActioneur.begin(); it != m_moduleActioneur.end(); ++it) {
        if(it->regA == adresse) {
            addrFind = true;
            m.regA=it->regA;
            m.regB=it->regB;
            m.regC=it->regC;
            m.regD=it->regD;
        }
    }

    for (std::list<Module>::iterator it=m_moduleCapteur.begin(); it != m_moduleCapteur.end(); ++it) {
        if(it->regA == adresse) {
            addrFind = true;
            m.regA=it->regA;
            m.regB=it->regB;
            m.regC=it->regC;
            m.regD=it->regD;
        }
    }

    for (std::list<Module>::iterator it=m_moduleMemoire.begin(); it != m_moduleMemoire.end(); ++it) {
        if(it->regA == adresse) {
            addrFind = true;
            m.regA=it->regA;
            m.regB=it->regB;
            m.regC=it->regC;
            m.regD=it->regD;
        }
    }

    // if((addrDispo==255) && (!addrFind))addrDispo=0; //les 255 adresses son utiliser // bravo le robot doit etre under heavy load.
    //  }

    return addrFind;
}
bool MemRegistre::isAdresseValide(const char &adresse)
{
    Module dummy;
    return isAdresseValide(adresse,dummy);
}

Module MemRegistre::firstActioneur(void)
{
    m_positionActioneur =m_moduleActioneur.begin();
    return *m_positionActioneur;//m_moduleActioneur.begin();
}
Module MemRegistre::nextActioneur(void)
{
    if(m_moduleActioneur.end()!= m_positionActioneur)
        m_positionActioneur++;

    return *m_positionActioneur;//return m_moduleActioneur[m_positionActioneur];
}

Module MemRegistre::firstCapteur(void)
{
    m_positionCapteur =m_moduleCapteur.begin();
    return *m_positionCapteur;//return m_moduleCapteur[m_positionCapteur];
}
Module MemRegistre::nextCapteur(void)
{
    if(m_moduleCapteur.end()!= m_positionCapteur)
        m_positionCapteur++;

    return *m_positionCapteur;//return m_moduleActioneur[m_positionCapteur];
}
Module MemRegistre::firstMemoire(void)
{
    m_positionMemoire =m_moduleMemoire.begin();
    return *m_positionMemoire;//return m_moduleMemoire[m_positionMemoire];
}
Module MemRegistre::nextMemoire(void)
{
    if(m_moduleMemoire.end()!= m_positionMemoire)
        m_positionMemoire++;

    return *m_positionMemoire;//return m_moduleActioneur[m_positionMemoire];
}

/**
 * MemRegistre.cpp
 * @author Alexandre Salconi-Denis
 * @version 3.01
 * @date 06 mars 2014
 *  Created on: Mar 10, 2015
 *      Author: salco
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
     debug(DEBUG_GETADDR,"\n\rGetAddrDispo::Debut");
    //list<Module>::iterator it1;
    unsigned char addrDispo=(startValue==0)?1:startValue;
    debug(DEBUG_GETADDR,"\n\r addrDispo: %02X",addrDispo);
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
        debug(DEBUG_GETADDR,"\n\r   is %02X valide %i",addrDispo,addrFind);
        if((addrDispo==255) && (!addrFind))addrDispo=0; //les 255 adresses son utiliser // bravo le robot doit etre under heavy load.
    }
    if(addrDispo != 0)
        addrDispo--;//patch vue quil fait un ++ a la fin de la boucle pour rien
    //else
      //  addrDispo=0;
        
    debug(DEBUG_GETADDR,"\n\rGetAddrDispo::Fin");
    return addrDispo;
}
bool MemRegistre::isAdresseValide(const char &adresse, Module &m )
{
    debug(DEBUG_ISVALIDE,"\n\risAdresseValide::Debut");
    list<Module>::iterator it1;
    bool addrFind=false;
    //Module templateModule;
    //for(unsigned char addrDispo=1; (addrDispo!=0)&&(!addrFind); addrDispo++) {

    debug(DEBUG_ISVALIDE,"\n\r  -search in: Actioneur");
    for (list<Module>::iterator it=m_moduleActioneur.begin(); it != m_moduleActioneur.end(); ++it) {
        debug(DEBUG_ISVALIDE,"\n\r  -if( %02X == %02X )",it->regA,adresse);
        if(it->regA == adresse) {
            addrFind = true;
            m.regA=it->regA;
            m.regB=it->regB;
            m.regC=it->regC;
            m.regD=it->regD;
        }
    }
    debug(DEBUG_ISVALIDE,"\n\r  -search in: Capteur");
    for (std::list<Module>::iterator it=m_moduleCapteur.begin(); it != m_moduleCapteur.end(); ++it) {
        debug(DEBUG_ISVALIDE,"\n\r  -if( %02X == %02X )",it->regA,adresse);
        if(it->regA == adresse) {
            addrFind = true;
            m.regA=it->regA;
            m.regB=it->regB;
            m.regC=it->regC;
            m.regD=it->regD;
        }
    }
    debug(DEBUG_ISVALIDE,"\n\r  -search in: Memoire");
    for (std::list<Module>::iterator it=m_moduleMemoire.begin(); it != m_moduleMemoire.end(); ++it) {
        debug(DEBUG_ISVALIDE,"\n\r  -if( %02X == %02X )",it->regA,adresse);
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
    debug(DEBUG_ISVALIDE,"\n\risAdresseValide::Fin");
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

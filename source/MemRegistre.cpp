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
    m_positionActioneur = 0;
    m_positionCapteur = 0;
    m_positionMemoire = 0;
}
MemRegistre::~MemRegistre()
{
}
Module MemRegistre::firstActioneur(void)
{
    m_positionActioneur = 0;
    return m_moduleActioneur[m_positionActioneur];
}
Module MemRegistre::nextActioneur(void)
{
    if(m_moduleActioneur.getSize()> m_positionActioneur)
        m_positionActioneur++;

    return m_moduleActioneur[m_positionActioneur];
}

Module MemRegistre::firstCapteur(void)
{
    m_positionCapteur = 0;
    return m_moduleCapteur[m_positionCapteur];
}
Module MemRegistre::nextCapteur(void)
{
    if(m_moduleCapteur.getSize()> m_positionCapteur)
        m_positionCapteur++;

    return m_moduleCapteur[m_positionCapteur];
}
Module MemRegistre::firstMemoire(void)
{
    m_positionMemoire = 0;
    return m_moduleMemoire[m_positionMemoire];
}
Module MemRegistre::nextMemoire(void)
{
    if(m_moduleMemoire.getSize()> m_positionMemoire)
        m_positionMemoire++;

    return m_moduleMemoire[m_positionMemoire];
}

/**
  * @file       ListChainer.cpp
  * @brief      Cette class est une liste chainer pour les modules.
  * @author     Salco
  * @version    2.00
  * @date       12 mars 2015
  */
#include "ListChainer.h"

int m_item=0;

/**
 * @brief Constructeur de la classe LList
 */
ListChainer::ListChainer()
{
    m_head = 0;
    m_ptrList = m_head;
}
/**
 * @brief Fonction renvoyant un pointeur sur un node_t
 * @param pos la position desirer
 * @return un pointeur de node_t
 */
ListChainer::node_t *ListChainer::getAtPos(int pos) const
{
    node_t * tmpPtr;
    tmpPtr = m_head;
    int i=1 ;

    if ((pos <= m_item) && (pos > 0))
    {
        for(tmpPtr = m_head; ( i < pos) && (tmpPtr->m_next!= 0) ; tmpPtr = tmpPtr->m_next)i++;
    }
    return tmpPtr;
}
/**
 * @brief Fonction utiliser pour supprimer a un endroit dans la liste chainee
 * @param pos index de l'endroit a supprimer
 */
void ListChainer::remAtPos(int pos)
{
    if(pos == 0)
        remHead();

    else if(pos <= getSize())
    {
        node_t * tmpPtr = m_head;
        node_t * tmp;

        for(int i=0; i<pos-1; i++)
        {
            tmpPtr = tmpPtr->m_next;
        }

        tmp=tmpPtr->m_next;

        if(tmpPtr->m_next->m_next == 0)
            m_ptrList = tmpPtr;

        tmpPtr->m_next= tmpPtr->m_next->m_next;

        delete(tmp);
    }
    else
        return;

    m_item--;
}
/**
 * @brief Fonction utiliser pour supprimer la tete de la liste chainee
 */
void ListChainer::remHead()
{
    node_t * tmpPtr;
    tmpPtr = m_head->m_next;
    delete(m_head);
    m_head = tmpPtr;
}
/**
 * @brief Fonction utiliser pour supprimer toute la liste chainee
 */
void ListChainer::remAll()
{
    node_t * tmp;

    while(m_head!=0)
    {
        tmp = m_head->m_next;

        delete(m_head);

        m_head = tmp;
    }

}


/**
 * @brief fonction de swap entre les 2 contacts
 * @param indexA
 * @param indexB
 */
void ListChainer::swap(int indexA, int indexB)
{
    if((indexA <= m_item)&&(indexB <= m_item))
    {
        Module tmp(this->getAtPos(indexA)->m_node);

        this->getAtPos(indexA)->m_node =
                this->getAtPos(indexB)->m_node;

        this->getAtPos(indexB)->m_node = tmp;
    }
}
/**
 * @brief Fonction utiliser pour avoire la longueur de la liste chainee
 * @return  longueur de la liste chainee
 */
int ListChainer::getSize()
{
    return m_item;
}
/**
 * @brief Fonction utiliser pour ajouter a la fin de la liste chainee
 * @param newModule variable de type Module
 */
void ListChainer::addNode(Module newModule)
{
    node_t * tmp = new node_t(newModule);

    if(m_head == 0)
    {
        m_head = tmp;
        m_ptrList =  tmp;
    }

    else
    {
        m_ptrList->m_next=tmp;
        m_ptrList = tmp;
    }

    m_item++;
}
/**
 * @brief Constructeur de la classe node_t
 * @param contact
 */
ListChainer::node_t::node_t(Module contact):
    m_node(contact), m_next(0)
{
}

/**
 * @brief triRapidePartition Fonction de tri rapide, adapter pour la liste chainer
 * @param a index de debut desiree
 * @param b index de fin desiree
 * @author model inspirer de: wikipedia
 */
void ListChainer::triRapidePartition(int a, int b)//Implementation future//
{
    int q;

    if (a < b)
    {
        q = partitionner( a, b, *this);
        triRapidePartition( a, q);
        triRapidePartition( q+1, b);
    }
}

/**
 * @brief partitionner Seconde fonction du tri rapide
 * @param start index de debut desiree
 * @param end index de fin desiree
 * @param tmpList pointeur sur la liste chainee
 * @return index pour le tri rapide
 */
int ListChainer::partitionner(int start, int end, ListChainer& tmpList)
{//Implementation future ( Module na pas loperateur  < et > )//
    //int   i = start-1, j = end+1;
   // Module pivot=(*this)[start];

    while (1)
    {
     /*   do
            j--;
        while (tmpList[j] > pivot);

        do
            i++;
        while (tmpList[i] < pivot);

        if (i < j)
        {
            Module tmp(tmpList[i]);
            tmpList[i] = tmpList[j];
            tmpList[j] = tmp;
        }
        else
            return j;*/
    }
}


/**
 * @brief operator [] Operateur surchargent la methode operator[]
 * @param index
 * @return
 */
Module& ListChainer::operator [](int index)
{
    if((index >= 0) && (index < this->getSize()))
        return getAtPos(index+1)->m_node;
    else
    //Module bad;
    return  m_head->m_node;//bad ;
}

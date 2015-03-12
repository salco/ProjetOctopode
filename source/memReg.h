/**
  * @file       memReg.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef MEMREG_H
#define MEMREG_H

struct module
{
    char regA;
    char regB;
    char regC;
    };

class MemReg
{
    
    /**
     * @brief La classe node_t
     */
    class node_t
    {

    public:
        Contact m_node;
        node_t *m_next;

        /**
         * @brief Constructeur de la classe node_t
         * @param contact
         */
        node_t(Contact contact);
    };

    node_t *m_head;
    node_t *m_ptrList;

    /**
     * @brief Fonction renvoyant un pointeur sur un node_t
     * @param pos la position desirer
     * @return un pointeur de node_t
     */
    node_t *getAtPos(int pos)const;
    /**
     * @brief fonction de swap entre les 2 contacts
     * @param indexA
     * @param indexB
     */
    void  swap(int indexA, int indexB);

    /**
     * @brief partitionner Seconde fonction du tri rapide
     * @param start index de debut desiree
     * @param end index de fin desiree
     * @param tmpList pointeur sur la liste chainee
     * @return index pour le tri rapide
     */
    int partitionner(int start, int end, LListContact& tmpList);

public:
    /**
     * @brief Constructeur de la classe LList
     */
    LListContact();
    /**
     * @brief Fonction utiliser pour avoire la longueur de la liste chainee
     * @return  longueur de la liste chainee
     */
    int getSize ();
    /**
     * @brief Fonction utiliser pour ajouter a la fin de la liste chainee
     * @param newContact variable de type Contact
     */
    void addNode(Contact newContact);
    /**
     * @brief Fonction permettant la lecture d'un nom dans la liste chainee
     * @param index index de l'endroit desiree dans la liste chainee
     * @return nom desiree
     */
    QString getNameAt (int index);
    /**
     * @brief Fonction permettant la lecture d'un prenom dans la liste chainee
     * @param index index de l'endroit desiree dans la liste chainee
     * @param texte prenom desiree
     */
    QString getPrenameAt (int index);
    /**
     * @brief Fonction permettant la lecture d'un adresse courriel dans la liste chainee
     * @param index index de l'endroit desiree dans la liste chainee
     * @return courriel desiree
     */
    QString getMailAt (int index);
    /**
     * @brief Fonction permettant la lecture d'un numero de telephone dans la liste chainee
     * @param index index de l'endroit desiree dans la liste chainee
     * @return numero de telephone desiree
     */
    QString getTelAt (int index);
    /**
     * @brief Fonction utiliser pour supprimer a un endroit dans la liste chainee
     * @param pos index de l'endroit a supprimer
     */
    void  remAtPos(int pos);
    /**
     * @brief Fonction utiliser pour supprimer la tete de la liste chainee
     */
    void  remHead(void);
    /**
     * @brief Fonction utiliser pour supprimer toute la liste chainee
     */
    void  remAll(void);

    /**
     * @brief triRapidePartition Fonction de tri rapide, adapter pour la liste chainer
     * @param a index de debut desiree
     * @param b index de fin desiree
     * @author model inspirer de: wikipedia
     */
    void triRapidePartition(int a, int b);

    //node_t &operator [] (int index);

    /**
     * @brief operator [] Operateur surchargent la methode operator[]
     * @param index
     * @return
     */
    Contact &operator [](int index);
};
#endif // MEMREG_H/*




/**
  * @file       ListChainer.h
  * @brief      Cette class est une liste chainer pour les modules.
  * @author     Salco
  * @version    2.00
  * @date       12 mars 2015
  */
#ifndef LISTCHAINER_H
#define LISTCHAINER_H

/**
 * Structure des registe de memoire des modules
 *  @note 
 *  <B>Adresse du Périphérique:</B> i like banana.<BR>
 *  <B>Lier a quelle réaction:</B> i like banana.<BR>
 *  <B>Type de format:</B> i like banana.<BR>
 *  <B>Position Spatiale:</B> i like banana.<BR>
 *  <B>Type:</B> i like banana.<BR>
 *  <B>Sous-Type:</B> i like banana.
 */
struct Module {
    char regA; /**< Registre A.
                * <table border="1" style="border: 1px solid black; text-align: center;">
                * <tr>   
                *   <th colspan="4" style="border: 1px solid black">Adresse du Périphérique</th>
                *   <th colspan="3">Lier a quelle réaction</th>
                *   <th colspan="1">Type de format</th>
                * </tr>
                * <tr>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>                
                * </tr>
                * </table> */
    char regB; /**< Registre B.
                * <table border="1" style="border: 1px solid black; text-align: center;">
                * <tr>   
                *   <th colspan="2" style="border: 1px solid black">Type de format</th>
                *   <th colspan="6">Position Spatiale</th>
                * </tr>
                * <tr>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>                
                * </tr>
                * </table> */
    char regC; /**< Registre C.
                * <table border="1" style="border: 1px solid black; text-align: center;">
                * <tr>   
                *   <th colspan="2" style="border: 1px solid black">Type</th>
                *   <th colspan="6">Sous-Type</th>
                * </tr>
                * <tr>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>
                *   <td>0</td>                
                * </tr>
                * </table> */
};

/**
 * Liste chainée dédier au registre des modules
 */
class ListChainer
{
    /**
    * @brief La classe node_t
    */
    class node_t
    {

    public:
        Module m_node;
        node_t *m_next;

        /**
         * @brief Constructeur de la classe node_t
         * @param contact
         */
        node_t(Module module);
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
    int partitionner(int start, int end, ListChainer& tmpList);//Implementation future ( Module na pas loperateur  < et > )//

public:
    /**
     * @brief Constructeur de la classe LList
     */
    ListChainer();
    /**
     * @brief Fonction utiliser pour avoire la longueur de la liste chainee
     * @return  longueur de la liste chainee
     */
    int getSize ();
    /**
     * @brief Fonction utiliser pour ajouter a la fin de la liste chainee
     * @param newModule variable de type Module
     */
    void addNode(Module newModule);
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
    void triRapidePartition(int a, int b);//Implementation future//

    //node_t &operator [] (int index);

    /**
     * @brief operator [] Operateur surchargent la methode operator[]
     * @param index
     * @return Retourne le Module desirer.
     */
    Module &operator [](int index);

};

#endif // LISTCHAINER_H//
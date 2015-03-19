
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
    unsigned char regA; // adresse module
    char regB; /**< Registre B.
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
    char regC; /**< Registre C.
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
    char regD; /**< Registre D.
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
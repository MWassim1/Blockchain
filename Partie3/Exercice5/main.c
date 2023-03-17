#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "exercice5.h"

int main() {
    srand(time(NULL));

    /* création de clés */
    Key* pKey = malloc(sizeof(Key));
    Key* sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey,3,7);

    CellKey* c = create_cell_key(pKey);
    c = insert_cell_key(c, sKey);

    free(pKey); 
    free(c->next);
    free(c);
    // fgets puis lecture ligne en str, puis conversion protected

    /* test delete_cell_key */
    CellKey* sKeyCell = create_cell_key(sKey); 
    delete_cell_key(sKeyCell);

    /* test lecture */
    c = read_public_keys("keys.txt");
    printf("test print_list_keys keys.txt\n");
    print_list_keys(c);
    delete_list_keys(c); 
    

    c = read_public_keys("candidats.txt");
    printf("test print_list_keys candidats.txt\n");
    print_list_keys(c);
    delete_list_keys(c);
    
    /* test creation ProtectedCell avec create_cell_protected */

    /* génération protected : */
    pKey = malloc(sizeof(Key));
    sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey,3,7);
    char *mess = key_to_str(pKey);
    Signature* sgn = sign(mess, sKey);
    free(sKey);
    Protected* pr = init_protected(pKey, mess, sgn);
    CellProtected* LCP = create_cell_protected(pr);
    printf("test print_list_protected LCP après création\n");
    print_list_protected(LCP);

    /* test insertion : */
    Key* pKey2 = malloc(sizeof(Key));
    Key* sKey2 = malloc(sizeof(Key));
    init_pair_keys(pKey2, sKey2, 3, 7);
    char* mess2 = key_to_str(pKey2);
    Signature* sgn2 = sign(mess2,sKey2);
    free(sKey2);
    Protected *pr2 = init_protected(pKey2, mess2, sgn2);
    insert_cell_protected(&LCP,pr2);
    printf("test print_list_protected LCP après insertion\n");
    print_list_protected(LCP);
    delete_list_protected(LCP);
    

    /* test lecture fichier declarations avec read_protected */
    CellProtected* cPrDeclarations = read_protected("declarations.txt");
    printf("test affichage LCP avec print_list_protected :\n");
    print_list_protected(cPrDeclarations);
    delete_list_protected(cPrDeclarations);
    
    return 0;
}
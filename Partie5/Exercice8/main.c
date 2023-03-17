#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "../../Partie3/Exercice5/exercice5.h"
#include "../../Partie4/Exercice6/exercice6.h"
#include "../Exercice7/exercice7.h"
#include "exercice8.h"

int main() {
    /*Creation d'un arbre*/
    /* forme de l'arbre :
          racine
           / \
          a1  b1
             / \
            b2  b21    */
    int d = 2;
    Block* block1 = create_block_test(NULL, d);
    Block* block2 = create_block_test(block1->hash, d);
    Block* block3 = create_block_test(block1->hash, d);
    Block* block4 = create_block_test(block3->hash, d);
    Block* block5 = create_block_test(block3->hash, d);
    CellTree* racine = create_node(block1);
    CellTree* a1 = create_node(block2);
    CellTree* b1 = create_node(block3);
    CellTree* b2 = create_node(block4);
    CellTree* b21 = create_node(block5);
    printf("DONNEES\n");
    printf("racine : %s\n a1 %s \n b1 %s \n b2 %s\n b21 %s\n", block1->hash, block2->hash, block3->hash, block4->hash, block5->hash);
    add_child(racine,a1);
    add_child(racine,b1);
    add_child(b1,b2);
    add_child(b1,b21);

    /*Affichage*/
    printf("\nARBRE\n");
    print_tree(racine);

    /*Recherche*/
    CellTree* high = highest_child(racine);
    printf("\nHIGH CHILD\n");
    print_tree(high);
    CellTree* lnode = last_node(racine);
    printf("\nLAST NODE\n");
    print_tree(lnode);
    printf("\nLISTE DECLARATION\n");
    CellProtected* cp = liste_declaration_block(racine);
    print_list_protected(cp);

    /*Liberation de la memoire*/
   //delete_list_protected(cp);
   //delete_tree(racine);
    
    return 0;
}

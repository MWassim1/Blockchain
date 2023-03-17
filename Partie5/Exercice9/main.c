#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "../../Partie3/Exercice5/exercice5.h"
#include "../../Partie4/Exercice6/exercice6.h"
#include "../Exercice7/exercice7.h"
#include "../Exercice8/exercice8.h"
#include "exercice9.h"

#define sizeC 5
#define sizeV 1000
#define d 2

int main(){
    srand(time(NULL));
    generate_random_data(sizeV, sizeC);
    CellKey* votes = read_public_keys("keys.txt");
    CellKey* candidats = read_public_keys("candidats.txt");
    CellProtected* cp = read_protected("declarations.txt");
    int cmp = 0; //compteur des votes
    int b = 0; //variable pour le nom des fichiers blocks
    char * name = (char*)malloc(sizeof(char)*100); //nom des fichiers blocks
    CellTree* tree = NULL;
    while(cp){
        submit_vote(cp->data);
        cmp += 1;
        if(cmp%10 == 0){ //tous les 10 votes
            create_block(tree, votes->data, d);
            sprintf(name, "Block_%d",b);
            add_block(d, name);
            b++;
        }
        cp = cp->next;
    }
    tree = read_tree(d);
    print_tree(tree);
    Key* winner = compute_winner_BT(tree, candidats, votes, sizeC, sizeV);
    printf("GAGNANT : %s \n", key_to_str(winner));

    free(name);
    delete_list_keys(votes);
    delete_list_keys(candidats);
    delete_list_protected(cp);
    printf("tree : %p\n",tree);
    //delete_tree(tree);
    return 0;
}

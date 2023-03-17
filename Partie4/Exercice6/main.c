#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "../../Partie3/Exercice5/exercice5.h"
#include "exercice6.h"

/*attention : ces valeurs doivent correspondre aux donnees generees*/
#define nv 1000
#define nc 5

int main() {

    // lecture des déclarations de vote 
    CellProtected* decl = read_protected("declarations.txt"); 
    // Suppression des fraudes 
    delete_fraud(&decl); 
    
    
    // test creation hashcell 
    // création de clés 
    Key* pKey = malloc(sizeof(Key));
    Key* sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey,3,7);
    free(sKey);

    HashCell* hc = create_hashcell(pKey);
    

    // test fonction de hachage 
    int pos = hash_function(hc->key,nv);
    printf("Position dans le tableau du voteur de cle publique pKey : %d\n",pos);
    free(hc->key);
    free(hc);
    
    // test creation de table de hachage 
    // lecture des clés 
    CellKey* voters = read_public_keys("keys.txt"); 
    
    HashTable* voteurs = create_hashtable(voters,nv);
    delete_hashtable(voteurs);

    
    
    // test determination du gagnant 

    // lecture des clés concernées 
    CellKey* candidates = read_public_keys("candidats.txt"); 
    

    HashTable* candidats = create_hashtable(candidates,nc);    
    delete_hashtable(candidats);
    Key* winner = compute_winner(decl, candidates, voters,nc,nv);
    char * str_winner = key_to_str(winner);
    printf("WINNER : %s\n",str_winner);
    free(str_winner);
    delete_list_keys(candidates);
    delete_list_keys(voters);
    delete_list_protected(decl);
    

    return 0;
}

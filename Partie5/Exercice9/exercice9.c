#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "../../Partie3/Exercice5/exercice5.h"
#include "../../Partie4/Exercice6/exercice6.h"
#include "../../Partie5/Exercice7/exercice7.h"
#include "../../Partie5/Exercice8/exercice8.h"
#include "exercice9.h"

void submit_vote(Protected* p){
    FILE* f = fopen("./Blockchain/Pending_votes.txt", "a");
    if(f){
        char* s = protected_to_str(p);
        fprintf(f,"%s\n",s);
        free(s);
    }
    else{
        printf("Erreur ouverture ficher submit_vote\n");
        return;
    }
    fclose(f);
}

void create_block(CellTree* tree, Key* author, int d){
    Block* b = (Block*) malloc(sizeof(Block));
    /*Creation cles author*/
    b->author = author;
    /*Creation CellProtected votes a 2 cellules*/
    CellProtected* cp = read_protected("./Blockchain/Pending_votes.txt");
    b->votes = cp;
    /*hash et previous_hash*/
    b->nonce = 0;
    b->hash = NULL;
    if(tree){
        b->previous_hash = (unsigned char *)strdup((char * )last_node(tree)->block->hash);
    }
    else{
        b->previous_hash = NULL;
    }
    char* str = block_to_str(b);
    char * h = str_to_hash(str);
    b->hash =(unsigned char *)strdup(h);
    /*nonce*/
    compute_proof_of_work(b, d);
    free(str);
    free(h);
    write_file_block("./Blockchain/Pending_block", b);
    remove("./Blockchain/Pending_votes.txt");
}

void add_block(int d, char* name){
    Block* b = read_file_block("Blockchain/Pending_block",d);
    if(verify_block(b,d)==0){
        printf("Block invalide\n");
        remove("./Blockchain/Pending_block");
        return;
    }
    char * s = (char *)malloc(sizeof(char)*256);
	sprintf(s, "Blockchain/%s",name);
    write_file_block(s, b);
    free(s);
    remove("./Blockchain/Pending_block");
}

CellTree* read_tree(int d){
    DIR* rep = opendir ("./Blockchain/") ;
    if ( rep != NULL ) {
        struct dirent* dir ;
        /*on recupere la taille du tableau*/
        int cmp = 0;
        CellTree* res;
	    while((dir = readdir(rep))){
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                cmp++;
            }
    	}
        rewinddir(rep); //retour au début du repertoire
        /*Creation, initialisation et remplissage du tableau*/
        CellTree* T[cmp];
        for(int t = 0; t<cmp;t++){
            T[t]=NULL;
        }
        int tcmp = 0;
        Block* b;
        char * s = (char *)malloc(sizeof(char)*256);
        char* previous_hash = NULL;
        while ((dir = readdir(rep))) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 ){
                sprintf(s, "Blockchain/%s",dir->d_name);
                b = read_file_block(s,d);
                b->previous_hash = (unsigned char*) previous_hash;
                T[tcmp] =create_node(b);
                previous_hash = (char*) b->hash;
                tcmp++;
                remove(s);
            }
        }
        /*ajout dans l'arbre*/
        for(int i = 0; i<cmp; i++){
            for(int j = 0; j<cmp; j++){
                if((T[j]->block->previous_hash!=NULL)&&strcmp((const char*)T[j]->block->previous_hash,(const char*) T[i]->block->hash)==0){
                    add_child(T[i], T[j]);
                }
            }
        }

        /*recherche de la racine*/
        for(int c = 0; c<cmp; c++){
            if(T[c]->father == NULL){
                res = T[c];
            }
        }
        free(s);
        //delete_block(b);
        closedir ( rep ) ;
        return res;
    }
    printf("Erreur ouverture read_tree\n");
    return NULL;
}

Key* compute_winner_BT(CellTree* tree, CellKey* candidats, CellKey* voters, int sizeC, int sizeV){
    CellProtected* fusion = liste_declaration_block(tree);
    delete_fraud(&fusion);
    Key* winner = compute_winner(fusion, candidats, voters, sizeC, sizeV);
    delete_list_protected(fusion);
    return winner;
}

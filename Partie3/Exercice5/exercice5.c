#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "exercice5.h"


/*LISTE CHAINEE DE CLES*/

CellKey* create_cell_key(Key* key){
    CellKey* c = (CellKey*) malloc(sizeof(CellKey));
    if (c) {
        c->data = key;
        c->next = NULL;
        return c;
    }
    printf("Erreur allocation create_cell_key\n");
    return NULL;
}

CellKey* insert_cell_key(CellKey* LCK, Key* data){
    CellKey* c = create_cell_key(data);
    c->next = LCK; 
    return c;
}
CellKey* read_public_keys(char* nomFic) { 
    if (!strcmp(nomFic,"keys.txt")) {
        FILE* keys = fopen("keys.txt","r");
        if (keys) {
            char buffer[256];
            fgets(buffer,256,keys);
            int i = 0;
            while (buffer[i] != ' ') {
                i++;
            } 
            buffer[i] = '\0';
            char* pKeyStr = strdup(buffer);
            Key* pKey = str_to_key(pKeyStr);
            free(pKeyStr);
            CellKey* c = create_cell_key(pKey);
            while (fgets(buffer,256,keys)) {
                i = 0;
                while (buffer[i] != ' ') {
                    i++;
                } 
                buffer[i] = '\0';
                pKeyStr = strdup(buffer);
                pKey = str_to_key(pKeyStr);
                free(pKeyStr);
                c = insert_cell_key(c, pKey);
            }
            fclose(keys);
            return c;
        }
        printf("Erreur ouverture fichier keys.txt read_public_keys\n");
        return NULL;
    }
    if (!strcmp(nomFic,"candidats.txt")) {
        FILE* candidats = fopen("candidats.txt","r");
        if (candidats) {
            char buffer[256];
            fgets(buffer,256,candidats);  
            char* pKeyStr = strdup(buffer);
            Key* pKey = str_to_key(pKeyStr);
            free(pKeyStr);
            CellKey* c = create_cell_key(pKey);
            while (fgets(buffer,256,candidats)) { 
                pKeyStr = strdup(buffer);
                pKey = str_to_key(pKeyStr);
                free(pKeyStr);
                c = insert_cell_key(c, pKey);
            }
            fclose(candidats);
            return c;
        }
        printf("Erreur ouverture fichier candidats.txt read_public_keys\n");
        return NULL;
    }
    printf("nom fichier non valide read_public_keys\n");
    return NULL;
}

void print_list_keys(CellKey* LCK){
    CellKey* tmp = LCK;
    while(tmp){
        char* strKey = key_to_str(tmp->data);
        printf("%s\n",strKey);  
        free(strKey);
        tmp = tmp->next; 
    }
}

void delete_cell_key(CellKey* c){
    if(c){
        free(c->data);
        free(c);
    }
}

void delete_list_keys(CellKey* LCK){
    CellKey* tmp = LCK;
    while(LCK){ 
        tmp = tmp->next;
        delete_cell_key(LCK);
        LCK=tmp;
    }
}

/*LISTE CHAINEE DE DECLARATIONS SIGNEES */

CellProtected* create_cell_protected(Protected* pr){
    CellProtected* c = (CellProtected*) malloc(sizeof(CellProtected));
    if (c) {
        c->data = pr;
        c->next = NULL;
        return c;
    }
    printf("Erreur allocation create_cell_protected\n");
    return NULL;
}

void insert_cell_protected(CellProtected** LCP, Protected* pr){
    /* rajouter securite memoire ? déjà présent dans create cell protected
    peut être mieux de passer liste par copie et retourner nouvelle? */ 
    CellProtected* c = create_cell_protected(pr);
    c->next = *LCP;
    *LCP = c;
}

CellProtected* read_protected(char* nomFic) {
    /* marche pas avec 1000 candidats générés mais marche avec 100 ?
    ou peut-être utilisé ancienne génération donc marchait pas ? */
    FILE* declarations = fopen(nomFic,"r");
    if (declarations) {
        char buffer[256];
        fgets(buffer,256,declarations);
        char* prStr = strdup(buffer);
        Protected* pr = str_to_protected(prStr);
        free(prStr);
        CellProtected* cPr = create_cell_protected(pr);
        while (fgets(buffer,256,declarations)) {
            prStr = strdup(buffer);
            pr = str_to_protected(prStr);
            free(prStr);
            insert_cell_protected(&cPr,pr);
            /* peut etre mieux pas passer par adresse methode*/ 
        } 
        fclose(declarations);
        return cPr;
    }
    printf("Erreur ouverture read_protected\n");
    return NULL;
    
}

void print_list_protected(CellProtected* LCP){
    CellProtected* tmp = LCP;
    // var parcours pour ne pas modifier liste
    while (tmp) {
        char* prStr = protected_to_str(tmp->data);
        printf("%s\n",prStr);
        free(prStr);
        tmp = tmp->next;
    } 
}

void delete_cell_protected(CellProtected* cp){ 
    free(cp->data->pKey);
    free(cp->data->mess);
    free(cp->data->sgn->content);
    free(cp->data->sgn);
    free(cp->data);
    free(cp);
}

void delete_list_protected(CellProtected* LCP){
  CellProtected* tmp = LCP;
  CellProtected* prev = LCP;
  while(tmp){ 
    tmp = tmp->next; 
    delete_cell_protected(prev); 
    prev = tmp; 
  }
}

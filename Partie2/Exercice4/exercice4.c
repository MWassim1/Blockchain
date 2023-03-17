#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../Exercice3/exercice3.h"
#include "exercice4.h"

void generate_random_data(int nv, int nc) { 
    /* Générer nv couples de clés représentant les nv citoyens
    et les stocker dans keys.txt */
    FILE *keys = fopen("keys.txt","w");
    /* keys.txt : couple (publique,secrète) pour nv citoyens) */
    Key* pKey;
    Key* sKey;
    Key* pKeyTab[nv];
    Key* sKeyTab[nv];
    char* pKeyStrTab[nv]; 
    
    int i;

    for (i = 0; i<nv; i++) {
        pKey = malloc(sizeof(Key)); 
        sKey = malloc(sizeof(Key)); 
        pKeyTab[i] = pKey;
        sKeyTab[i] = sKey;
        init_pair_keys(pKey,sKey,3,7);
        /* boucle de vérification de doublons */
        for (int j = 0; j<i; j++) {
            if (pKey->val == pKeyTab[j]->val) {
                /* si doublon détecté, regénère clés et recommence boucle */
                //printf("doublon détecté, regénère clés\n");
                init_pair_keys(pKey,sKey,3,7);
                j = 0;
            }
        }
        char* pKeyStr = key_to_str(pKey);
        pKeyStrTab[i] = pKeyStr;
        char* sKeyStr = key_to_str(sKey);
        fprintf(keys,"%s %s\n", pKeyStr, sKeyStr); 
        free(sKeyStr);
    }
    fclose(keys);
    
   /* selectionne nc clés publiques, définit nc candidats 
    et les stocke dans candidats.txt */
    FILE *candidats = fopen("candidats.txt","w");
    /* candidats.txt : clés publiques candidats */
    char* candidatsPKeyStrTab[nc];
    int tirage;
    int tabTirage[nc];
    /* détection candidats doublons */
    /*initialisation du tableau de tirages */ 
    for (i = 0; i<nc; i++) {
        tabTirage[i] = -1;
    }
    /* tirage au sort des candidats */
    for (i = 0; i<nc; i++) {
        tirage = rand()%nv; 
        for (int j = 0; j<=i; j++){
            if (tabTirage[j] == tirage) {
                j = 0;
                tirage = rand()%nv;
                printf("candidat doublon détecté, nouveau tirage\n");
            }
        } 
        tabTirage[i] = tirage;
        char* choix = pKeyStrTab[tirage]; 
        candidatsPKeyStrTab[i]=choix;
        fprintf(candidats, "%s\n", choix); 
    }
    fclose(candidats);

    /*génère une déclaration pour chaque citoyen (candidat
    choisi aléatoirement et stocke dans declarations.txt)*/
    FILE* declarations = fopen("declarations.txt","w");
    /* un protected_to_str par ligne (clé privée, message, signature) */
    Signature *sgn;
    Protected *pr;
    char* mess; //candidat pour lequel on vote
    for (i = 0; i<nv; i++) {
        int tirage = rand()%nc;
        mess = candidatsPKeyStrTab[tirage]; 
        sgn = sign(mess,sKeyTab[i]); 
        pr = init_protected(pKeyTab[i],mess,sgn); 
        char* prStr = protected_to_str(pr);
        fprintf(declarations, "%s\n", prStr);
        free(prStr); 
        free(sgn->content);
        free(sgn);
        free(pr);
    }
    fclose(declarations);

    for (i = 0; i<nv; i++) { 
        free(pKeyTab[i]);
        free(sKeyTab[i]);
        free(pKeyStrTab[i]);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "../../Partie3/Exercice5/exercice5.h"
#include "exercice6.h"

void delete_fraud(CellProtected** LCP){
    CellProtected* tmp = *LCP;
    CellProtected* prev = *LCP;
    int cpt = 0;
    if (!verify(tmp->data)) {
        *LCP = tmp->next;
        delete_cell_protected(prev);
        tmp = *LCP;
        prev = *LCP;
    }
    else {
        tmp = tmp->next;
    }
    while(tmp){ 
        if(!verify(tmp->data)){ 
            prev->next = tmp->next; 
            delete_cell_protected(tmp);
            tmp = prev->next;
            cpt++;
        }
        else {
            prev = tmp;
            tmp = tmp->next; 
        }
    }
    printf("Nombre de fraudes détectées : %d\n",cpt);
}


HashCell* create_hashcell(Key* key){
    HashCell* hc = malloc(sizeof(HashCell));
    hc->key = key;
    hc->val = 0;
    return hc;
}

int hash_function(Key* key, int size){
    return ((key->val + key-> n) % (size-1))*((sqrt(5)-1)/2);
}

int find_position(HashTable* t, Key* key){
    int pos = hash_function(key, t->size);
    char *tmp = NULL , *str_key = NULL;
    if(t->tab[pos]->key != NULL){
        tmp = key_to_str(t->tab[pos]->key);
        str_key = key_to_str(key);
        if(strcmp(tmp, str_key)==0  ){
            free(tmp);free(str_key);
            return pos;
        }
        free(tmp);free(str_key);
    }
    while(pos < t->size  && t->tab[pos]->key != NULL ){
        tmp = key_to_str(t->tab[pos]->key);
        str_key = key_to_str(key);
        if(strcmp(tmp, str_key)==0){
             free(tmp);free(str_key);
            return pos ;
        }
        free(tmp);free(str_key);
        pos++;
    }
    return pos;
}

HashTable* create_hashtable(CellKey* keys, int size){
    HashTable* ht = malloc(sizeof(HashTable));
    if(ht){
        ht->size = size;
        ht->tab = (HashCell**)malloc(sizeof(HashCell*)*size);
        if(ht->tab){
            for(int i = 0 ; i<size ; i ++){
                ht->tab[i] = create_hashcell(NULL); // Initialise a NULL afin de retrouver quelle case est libre. 
                if (!ht->tab[i]){
                    printf("erreur malloc dans create_hashtable\n");
                    for(int j = 0 ; j <  i ; j++){ // On libère les cases qui ont été allouées.
                        free(ht->tab[j]);
                    }
                    free(ht);
                    return NULL;
                }

            }
            while(keys){
                HashCell *tmp = create_hashcell(keys->data);
                int pos = find_position(ht,tmp->key);
                free( ht->tab[pos]); // On libère le HashCell qui est à NULL 
                ht->tab[pos] = tmp ; // Et on le remplace par le nouveau Hashcell
                keys = keys->next;
            }
            return ht ;
        }
        printf("erreur malloc pour ht->tab dans create_hashtable\n");
        free(ht);
        return NULL;
    }
    printf("erreur malloc create_hashtable\n");
    return NULL;
}
void delete_hashtable(HashTable* t){
    if (t){
        for(int i = 0 ; i < t-> size ; i++ ){
            if(!(t->tab[i]->key))
                free(t->tab[i]->key);
            free(t->tab[i]);
        }
        free(t->tab);
        free(t);
    }
}


Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){
    HashTable* hv = create_hashtable(voters, sizeV);
    HashTable* hc = create_hashtable(candidates, sizeC); 
    Key *  tmp_Kmess = NULL ;
    while(decl){
        Protected* tmp = decl->data;
        int posV = find_position(hv,tmp->pKey);
        if( posV < sizeV ){ //la personne a le droit de voter 
            if(hv->tab[posV]->val == 0){ //la personne n'a pas encore voté
                tmp_Kmess = str_to_key(tmp->mess);
                int  posC = find_position(hc,tmp_Kmess);
                if(posC<sizeC){ //le vote porte bien sur un candidat de l'élection
                    hv->tab[posV]->val = 1;
                    hc->tab[posC]->val +=1 ;
                }
                free(tmp_Kmess);
            }        
        }
        decl = decl->next;
    }
    //Retourne  le  vainqueur de l'élection 

    int max = hc->tab[0]->val , winner = 0  ;
    char * tmp_key = key_to_str(hc->tab[0]->key);
    printf("C : %p %d %s\n",hc->tab[0]->key,hc->tab[0]->val,tmp_key);
    free(tmp_key);
    for (int i = 1 ; i < sizeC ; i++){
        tmp_key = key_to_str(hc->tab[i]->key);
        printf("C : %p %d %s\n",hc->tab[i]->key,hc->tab[i]->val, tmp_key);
        if (max < hc->tab[i]->val){
            max = hc->tab[i]->val;
            winner = i ; 
        }
        free(tmp_key);
    }
    delete_hashtable(hv);
    Key* ktmp = hc->tab[winner]->key;
    delete_hashtable(hc);
    return ktmp;
}

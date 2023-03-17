#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "exercice3.h"

void init_key(Key* key, long val, long n){
    key->val = val;
    key->n = n;
}

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size){
    long p = random_prime_number (low_size ,up_size , 5000) ;
    long q = random_prime_number (low_size ,up_size , 5000) ;
    long n = 0; 
    long s = 0;
    long u = 0;
    generate_key_values(p,q,&n,&s,&u);
    init_key(pKey,s,n);
    init_key(sKey,u,n);
}

char* key_to_str(Key* key) {
    char* str = malloc(sizeof(char)*100);
    sprintf(str,"(%lx,%lx)", key->val, key->n);
    str = realloc(str,strlen(str)+1); // +1 car strlen ne prend en compte  pas le \0
    return str;
}

Key* str_to_key(char* str) {
    Key* k = malloc(sizeof(Key));
    long val;
    long n;
    sscanf(str,"(%lx,%lx)", &val,&n);
    k->val = val;
    k->n = n;
    return k;
}

Signature* init_signature(long* content, int size) {
    Signature* s = malloc(sizeof(Signature));
    if (s) { 
        s->content = content;
        s->size = size;
        return s;
    }
    printf("Erreur allocation init_signature\n");
    return NULL;
}

Signature* sign(char* mess, Key* sKey) {
    /* permet de générer la signature associée à une déclaration de vote */
    long* content = encrypt(mess,sKey->val,sKey->n);
    int size = strlen(mess); /* attention : strlen ne retourne pas la longueur avec \0 inclus */
    Signature* s = init_signature(content,size);
    return s;
}

/* fourni */
char* signature_to_str(Signature* sgn) {
    char* result = malloc(16*sgn->size*sizeof(char));
    result[0] = '#';
    int pos = 1;
    char buffer[256];
    for (int i = 0; i<sgn->size; i++) {
        sprintf(buffer, "%lx", sgn->content[i]);
        for (int j = 0; j<strlen(buffer); j++) {
            result[pos] = buffer[j];
            pos = pos + 1;
        }
        result[pos] = '#';
        pos = pos + 1;
    }
    result[pos] = '\0';
    result = realloc(result, (pos+1)*sizeof(char));
    return result;
}

/* fourni */
Signature* str_to_signature(char* str) {
    int len = strlen(str);
    long* content = (long*) malloc(sizeof(long)*len);
    int num = 0;
    char buffer[256];
    int pos = 0;
    for (int i = 0; i<len; i++) {
        if (str[i] != '#') {
            buffer[pos] = str[i];
            pos = pos + 1;
        } 
        else {
            if (pos != 0) {
                buffer[pos] = '\0';
                sscanf(buffer, "%lx", &(content[num]));
                num = num + 1;
                pos = 0;
            }
        }
    }
    content = realloc(content, num*sizeof(long));
    return init_signature(content, num);
}

Protected* init_protected(Key* pKey, char* mess, Signature* sgn){
    /* attention : ne vérifie pas si la signature est valide */
    Protected* pr = malloc(sizeof(Protected));
    if(pr){
        pr->pKey = pKey;
        pr->mess = mess;
        pr->sgn = sgn;
        return pr;
    }
    printf("Erreur allocation init_protected\n");
    return NULL;
}
int verify(Protected* pr){
    if(pr){
        char *messDecrypt= decrypt(pr->sgn->content,pr->sgn->size,pr->pKey->val,pr->pKey->n);
        if(!strcmp(pr->mess,messDecrypt)) {
            //printf("verification signature reussie\n");
            free(messDecrypt);
            return 1;
        }
        free(messDecrypt);
    }
    //printf("verification signature fausse\n");
    return 0;
}




char* protected_to_str(Protected* pr) {
    char* pKeyStr = key_to_str(pr->pKey); 
    char* sgnStr = signature_to_str(pr->sgn);
    /*int lenPKey = strlen(pKey);*/
    size_t resultSize = (strlen(pKeyStr) + strlen(pr->mess) + strlen(sgnStr) + 3)*sizeof(char);
    /* 3 : 2 espaces et \0*/
    char* result = (char*) malloc(sizeof(char)*resultSize); 
    snprintf(result,resultSize, "%s %s %s",pKeyStr,pr->mess,sgnStr);
    free(pKeyStr);
    free(sgnStr);
    return result;
}

Protected* str_to_protected(char* str) {
    int i = 0; /* position dans str */
    char buffer[256]; 

    /* récupère pKey */
    while (str[i] != ' ') {
        buffer[i] = str[i];
        i++; 
    }
    buffer[i] = '\0';
    i++; /* evite d'ajouter un espace au buffer*/ 
    char* strPKey = strdup(buffer); 
    Key* pKey = str_to_key(strPKey);
    free(strPKey);
    
    /*recupère message */
    int j = 0;
    while (str[i] != ' ') {
        buffer[j] = str[i];
        i++;
        j++;
    }
    buffer[j] = '\0';
    char* mess = strdup(buffer);
    /*recupère signature*/
    i++; /* evite d'ajouter un espace au buffer */ 
    j = 0;
    while (str[i] != '\0') {
        buffer[j] = str[i];
        i++;
        j++;
    }
    buffer[j] = '\0';
    char* strSgn = strdup(buffer);
    Signature* sgn = str_to_signature(strSgn);
    free(strSgn);
    return init_protected(pKey,mess,sgn); 
}

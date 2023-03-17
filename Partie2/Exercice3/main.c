#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "exercice3.h"

int main (){

    srand(time(NULL));

    //Testing Init Keys
    Key* pKey = malloc(sizeof(Key));
    Key* sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey,3,7);
    printf("pKey: %lx, %lx\n", pKey->val, pKey->n);
    printf("sKey: %lx, %lx\n", sKey->val, sKey->n); 

    //Testing Key Serialization
    char* chaine = key_to_str(pKey);
    printf("key to str: %s \n", chaine);
    Key* k = str_to_key(chaine);
    printf("str_to_key: %ld, %ld \n", k->val, k->n); 

    //Testing signature
    //Candidate keys:
    Key* pKeyC = malloc(sizeof(Key));
    Key* sKeyC = malloc(sizeof(Key)); 
    init_pair_keys(pKeyC, sKeyC,3,7);

    //Declaration:
    char* mess = key_to_str(pKeyC);
    char* pKeyStr = key_to_str(pKey);
    printf("%s vote pour %s\n", pKeyStr, mess);
    Signature* sgn = sign(mess, sKey); 
    printf("signature: ");
    print_long_vector(sgn->content, sgn->size);
    printf("sgn size : %d\n",sgn->size);
    free(chaine); // On free chaine car on va réutiliser le même nom de variable
    chaine = signature_to_str(sgn);
    printf("signature to str: %s \n", chaine);
    free(sgn->content); // De même ici on est obligé de libérer 'sgn' . 
    free(sgn);
    sgn = str_to_signature(chaine);
    free(chaine);
    printf("str to signature: ");
    print_long_vector(sgn->content, sgn->size);
    
    
    //Testing protected:
    Protected* pr = init_protected(pKey, mess, sgn);
    
    // Verification:
    if (verify(pr)) {
        printf("Signature valide\n");
    }
    
    else {
        printf("Signature non valide\n");
    } 
    chaine = protected_to_str(pr);
    free(sgn->content);
    free(sgn);
    free(pr);
    printf("protected_to_str : %s\n",chaine);
    pr = str_to_protected(chaine);
    free(chaine); 
    free(pKeyStr);
    pKeyStr = key_to_str(pr->pKey);
    char* sgnStr = signature_to_str(pr->sgn);
    printf("str_to_protected : %s %s %s\n", pKeyStr, pr->mess, sgnStr);
    free(pr->pKey); 
    free(pr->mess);
    free(pr->sgn->content); 
    free(pr->sgn);
    free(pr);
    free(pKey);
    free(sKey); 
    free(k);
    free(pKeyC);
    free(sKeyC); 
    free(mess);
    free(pKeyStr);
    free(sgnStr);

    return 0;    
}

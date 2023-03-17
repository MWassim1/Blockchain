#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "../../Partie3/Exercice5/exercice5.h"
#include "../../Partie4/Exercice6/exercice6.h"
#include "exercice7.h"


void write_file_block(char* nomFic, Block* b){
    /* Ecrit dans un fichier le block 'b' , le fichier sera du format : 
                    - author 
                    - hash 
                    - previous_hash
                    - nonce
                    - votes (1er CellProtected)
                    - votes (2eme CellProtected)
                    .
                    .
                    .
                                                                            */
    FILE* f = fopen(nomFic,"w");
    if(f){
       char * str =   key_to_str(b->author) ; 
       fprintf(f, "%s \n",str);
       free(str);
       int len =strlen((char*)b->hash);
       for (int i = 0; i < len ; i ++){
            fprintf ( f,"%02x"  ,b->hash[ i ]) ;
       }

        fputc('\n',f);
        if(b->previous_hash){
            for (int i = 0; i < SHA256_DIGEST_LENGTH ; i ++)
                fprintf ( f,"%02x"  ,b->previous_hash[ i ]) ;
            fputc('\n',f);
        }
        else {
            fprintf(f,"%s \n",b->previous_hash);
        }
        fprintf(f,"%d \n",b->nonce);
        char *pStr;
        CellProtected * tmp = b->votes ;
        while(tmp){
            pStr = protected_to_str(tmp->data);
            fprintf(f, "%s \n",pStr);
            free(pStr);
            tmp = tmp->next;
        }
        fclose(f);   
    }
    else{
        printf("Erreur ouverture write_file_block\n");
    }
}

Block* read_file_block(char* nomFic,int d ){
    /* lit dans un fichier et renvoie un block , le fichier est du format : 
                    - author 
                    - hash 
                    - previous_hash
                    - nonce
                    - votes (1er CellProtected)
                    - votes (2eme CellProtected)
                    .
                    .
                    .
                                                                            */
    Block* b = (Block*) malloc(sizeof(Block));
    FILE* f = fopen(nomFic, "r");
    if(b){
        char buffer[256];
        fgets(buffer,256,f);
        char* keyStr = strdup(buffer);
        b-> author = str_to_key(keyStr);
        free(keyStr);
        fgets(buffer,256,f);
        b->hash = (unsigned char*) strdup(buffer);
        fgets(buffer,256,f);
        if(strcmp(buffer,"(null) \n")==0){ /* le block n'a pas de previous_hash*/
            b->previous_hash = NULL ;
        }
        else {
            b->previous_hash = (unsigned char*) strdup(buffer);
        }
        fgets(buffer,256,f);
        b->nonce = atoi(buffer);
        Protected *pr;
        char* prStr;
        fgets(buffer,256,f); /*premier Protected de CellProtected*/
        prStr = strdup(buffer);
        pr = str_to_protected(prStr);
        free(prStr);
        CellProtected* cPr = create_cell_protected(pr);
        while (fgets(buffer,256,f)) {
            prStr = strdup(buffer);
            pr = str_to_protected(prStr);
            free(prStr);
            insert_cell_protected(&cPr,pr); 
        }
        b->votes = cPr;
        fclose(f);
        compute_proof_of_work(b, d);
        return b;
    }
    printf("Erreur ouverture read_protected\n");
    return NULL;
}

char* block_to_str(Block* b){
    char * s = key_to_str(b->author);
    char *s2 = "" ; 
    char tmp1[30] ;
    int b_previous_hash = 0 ; // Boolean pour vérifier s'il y a un previous_hash. Ce boolean est utilisé pour la libération de mémoire .
    sprintf(tmp1,"%d",b->nonce);      
    char * cnonce = strdup(tmp1);
    if(b->previous_hash != NULL){
        s2 = strdup((char*)b->previous_hash);
        b_previous_hash = 1 ; // 'b' a un previous_hash
    }
    char *s3 = protected_to_str(b->votes->data) ; 
    char *tmp2 = s3 ;
    CellProtected * btmp = b->votes->next;
    while(btmp){
        s3 = protected_to_str(btmp->data) ; 
        tmp2 = realloc(tmp2,sizeof(char)*(strlen(tmp2)+strlen(s3)+3)); // +2 pour les \0 et +1 pour l'ajout du " " à la ligne suivante
        strcat(tmp2," ");
        strcat(tmp2,s3);
        btmp = btmp->next;
    }
    int full_size = strlen(s)+strlen(s2)+strlen(tmp2)+strlen(cnonce)+5;
    char* str = (char*)malloc(sizeof(char)*full_size);
    strcpy(str,s); //  La clé de l’auteur.
    strcat(str," ");
    strcat(str,s2); // La valeur hachée du bloc précédent.
    strcat(str," ");
    strcat(str,tmp2); // Une représentation de ses votes.
    strcat(str," ");
    strcat(str,cnonce); // La preuve du travail 
    str[strlen(str)] = '\0';
    free(s);
    free(s3);
    free(tmp2);
    free(cnonce);
    if (b_previous_hash)
        free(s2);
    return str;
}


char * str_to_hash(char *str ){
    const unsigned char * s = (const unsigned char *) str;
    char * tmp = (char*) SHA256(s , strlen ( (const char*)s ) , 0) ;
    int len = strlen((char*)tmp);
    char *hex = (char*)malloc(sizeof(char)*((len*2)+7)) ; int k = 0 ;
    for (int i = 0 ; tmp[i]!= '\0'; i ++){
        sprintf((char*)(hex+i),"%02X",tmp[i]);
        k+=2;
    }
    hex[k++] = '\0';
    return hex;
}


void compute_proof_of_work(Block *B, int d){
    B->nonce = 0;
    int nb_0 = 0 ; // Nombre de 0 successifs en début de chaîne  
    for(int i = 0 ; B->hash[i]=='0'; i++){
        nb_0++;
    } 
    char *s = NULL;
    unsigned char* k = NULL;
    /*on change k jusqu'a ce que k commence par d zero successif*/
    while(nb_0 < d){
        B->nonce += 1;
        s = block_to_str(B);
        k = (unsigned char*)str_to_hash(s);
        nb_0 = 0 ;
        for(int i = 0 ; k[i]=='0'; i++){
            nb_0++;
        }
        free(s);
        free(k);
    }
}

int verify_block(Block* B, int d){
    char* suite_de_zeros= (char*)malloc(sizeof(char)*(d+1));
    for(int i = 0; i<d;i++)
        suite_de_zeros[i] = '0';
    char *s = block_to_str(B);
    char * h = str_to_hash(s);
    if(strncmp(h, suite_de_zeros, d)==0){
        /* le block est valide */
        free(h);
        free(suite_de_zeros);
        free(s);
        return 1;
    }
    /*le block n'est pas valide*/
    free(h);
    free(suite_de_zeros);
    free(s);
    return 0;
}

void time_compute_proof_of_work(Block* B){
    clock_t temps_initial = clock () ;
    clock_t temps_final = clock () ;
    FILE* f = fopen("ex7_temps.txt","w");
    for (int d = 0; d<2; d++){
        temps_initial = clock () ;
        compute_proof_of_work(B,d);
        temps_final = clock () ;
        fprintf(f,"%d %f \n",d,(( double ) ( temps_final - temps_initial )) / CLOCKS_PER_SEC);
    }
    fclose(f);
}

void delete_block(Block* B){
    /* les lignes en commentaires permettent de tout liberer , mais comme nous dit la consigne , on ne libere pas le champs author et les Protected*/
    if(B){
        //delete_list_protected(B->votes);
        while(B->votes){
            CellProtected * tmp = B->votes; 
            B->votes = B->votes->next;
            free(tmp);
        }
        free(B->hash);
        //free(B->author);
        free(B->previous_hash);
        free(B);
    }
}

Block* create_block_test(unsigned char * previous_hash, int d){
    Block* b = (Block*) malloc(sizeof(Block));
    /*Creation cles author*/
    Key* apKey = malloc(sizeof(Key));
    Key* asKey = malloc(sizeof(Key));
    init_pair_keys(apKey, asKey,3,7);
    b->author = apKey;
    free(asKey);
    /*Creation CellProtected votes a 2 cellules*/
    Key* pKey = malloc(sizeof(Key));
    Key* sKey = malloc(sizeof(Key));
    Key* pKey2 = malloc(sizeof(Key));
    Key* sKey2 = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey,3,7);
    init_pair_keys(pKey2, sKey2, 3, 7);
    char *mess = key_to_str(pKey);
    char* mess2 = key_to_str(pKey2);
    Signature* sgn = sign(mess, sKey);
    Signature* sgn2 = sign(mess2,sKey2);
    Protected* pr = init_protected(pKey, mess, sgn);
    CellProtected* LCP = create_cell_protected(pr);
    Protected *pr2 = init_protected(pKey2, mess2, sgn2);
    insert_cell_protected(&LCP,pr2);
    b->votes = LCP;
    free(sKey);
    free(sKey2);
    /*hash et previous_hash*/
    b->nonce = 0;
    b->hash = NULL;
    if(previous_hash){
        b->previous_hash =(unsigned char *)strdup((char * )previous_hash);  
    }
    else{
        b->previous_hash = NULL ;
    }
    char * str = block_to_str(b);
    char * h = str_to_hash(str);
    b->hash =(unsigned char *)strdup(h);
    /*nonce*/
    compute_proof_of_work(b, d);
    free(str);
    free(h);
    return b;
}

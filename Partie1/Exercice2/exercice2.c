#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../Exercice1/exercice1.h"

/* fourni */
long extended_gcd (long s, long t, long *u, long *v) {
    if (s == 0) {
        *u = 0;
        *v = 1;
        return t ;
    }
    long uPrim , vPrim;
    long gcd = extended_gcd (t%s, s, &uPrim, &vPrim);
    *u = vPrim - (t/s)*uPrim; 
    *v = uPrim;
    return gcd;
}


void generate_key_values(long p , long q , long *n , long *s, long *u){
    long  t , v ; 
    // Etape 1 
    *n  = p * q ;
    t = (p-1) * (q-1);
    do{
        *s = rand()%(t-1)+2;  // On génère aléatoirement des nombres inferieur à 't' ( Etape 2 )
    }while((extended_gcd(*s,t,u,&v) != 1)); // Etape 3 

    if(*u < 0 ){   /* Cette partie permet d'empêcher la génération de clé privé négative . Car génèrer des clés négatives a des conséquences sur la suite du code , pour le codage et donc par conséquent le décodage .
                    Donc quand 'u' est négatif on regénère 'p' et 'q' et on fait un appel récursif à  generate_key_values(p ,q , n , s, u).*/
        p = random_prime_number (3 ,7 , 5000) ; 
        q = random_prime_number (3,7 , 5000);
        generate_key_values(p ,q , n , s, u);
    }


}

long* encrypt(char* chaine, long s, long n){
    long * c = (long*)malloc(sizeof(long)*strlen(chaine)) ; // On alloue un tableau de long de taille strlen(chaine) , où dans chaque case on stock le caractère chiffré .
    if (c == NULL){
        printf("Erreur dans encrypt\n");
        return NULL;
    }
    for(int i  = 0 ; chaine[i] != '\0'; i ++){
        c[i] = modpow((int)chaine[i], s , n); 
    }
     
    return c ;
}
char *decrypt(long* crypted, int size, long u, long n){
    char *m = (char*)malloc(sizeof(char)*(size+1)) ; 
    /* On alloue un tableau de char de taille size+1 , car il ne faut pas oublier de reserver une case mémoire pour '\0'. */
    if(m == NULL){
        printf("Erreur dans decrypt\n");
        return NULL ;
    }
    for(int i = 0 ; i < size ; i++ ){
        m[i] = modpow(crypted[i], u, n);
    }
    m[size] = '\0';  // On ajoute le caractère de fin 
    return m ;
}

void print_long_vector(long *result , int size ){
    printf("Vector : [");
    for(int i = 0 ; i < size ; i ++){
        printf("%ld \t",result[i]);
    }
    printf("]\n");
}

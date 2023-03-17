#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "exercice1.h"

int is_prime_naive(long p ){
    for(int i = 2 ; i < p ; i ++){
        if (p%i == 0){
            return 0;
        }
    }
    return 1;
}

long modpow_naive(long a, long m, long n){
    long res = 1; 

    for (int i = 0 ; i < m ; i ++){
        res = (res * a ) % n; 
    }
    return res;
}

long modpow(long a , long m , long n ){
    long res ;
    //Cas de base 
    if (m == 0) {
        return 1 ; 
    }
    if (m==1) {
        return a%n;
    }
    //Si 'm' est pair 
    if (m%2 == 0) {
        res = modpow(a,m/2,n);
        res = (res*res)%n;
        return res  ;
    }
    // 'm' est impair 
    else {
        res = modpow(a,(int)(m/2),n);
        res = (res*res)%n ; 
        res  = (res*a)%n;
        return res;
    }
}

/* fourni */
int witness ( long a , long b , long d , long p ) {
    long x = modpow (a, d, p);
    if ( x == 1) {
        return 0;
    }
    for (long i = 0; i<b ; i++) {
        if (x == p-1) { 
            return 0;
        } 
        x = modpow(x, 2, p) ;
    }
    return 1;
}

/* fourni */
long rand_long ( long low , long up ) { 
    return rand() % (up - low +1) + low;
}

/* fourni */
int is_prime_miller (long p, int k) {
    if (p == 2) {
        return 1;
    }
    if (!( p & 1) || p <= 1) { //on verifie que p est impair et different de 1
        return 0;
    }
    //on determine b et d :
    long b = 0;
    long d = p - 1;
    while (!( d & 1) ) { //tant que d n’est pas impair
        d = d / 2;
        b = b + 1;
    }
    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a ;
    int i ;
    for ( i = 0; i < k ; i ++) {
        a = rand_long (2 , p -1) ;
        if ( witness (a ,b ,d , p ) ) {
        return 0;
        }
    }
    return 1;
}

long random_prime_number(int low_size , int up_size, int k ){
    int res ; long rand, low = 1 , up = 1 ; 

    for( int i = 0 ; i < low_size ; i ++)
        low *=2 ;  // On calcule (2^low_size)-2
    low-=2;
    for( int i = 0 ; i < up_size ; i++)
        up*=2 ; // On calcule (2^up_size)-1 
    up-=1;
    // On génère rand tant qu'il ne réussit pas le test de miller  pour k valeurs 
    do {
        rand = rand_long(low,up);
        res = is_prime_miller(rand,k); 
    }while(!res); 
    return rand ;
}
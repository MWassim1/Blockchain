#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../Exercice1/exercice1.h"
#include "exercice2.h"

int main () {
    //Generation de cle:
    for(int i = 0; i < 200; i++) {
        srand(time(NULL));
        long p = random_prime_number(3, 7, 5000);
        long q = random_prime_number(3, 7, 5000);
        printf("%ld %ld\n", p, q);
        while ( p == q ) {
            q = random_prime_number (3, 7, 5000) ;
        }
    
        long n, s, u;
        generate_key_values(p, q, &n, &s, &u); 
        
        u = abs(u);
        printf("cle publique = (%ld, %ld) \n", s, n);
        printf("cle privee = (%ld, %ld) \n", u, n);  
        if (u < 0) {
            long t = (p - 1) * (q - 1) ;
            u = u + t ; //on aura toujours s*u mod t = 1
        }
        char message[1000] = "Tu vas bien ?";

        int len = strlen(message);

        //Chiffrement:
        long* crypted = encrypt(message, s, n);
        
        printf("Initial message %s \n", message);
        printf("Encoded representation : \n");
        print_long_vector(crypted, len);
        //Dechiffrement
        char* decoded = decrypt(crypted, len, u, n);
        if (strcmp(message, decoded) != 0) {
            
            printf("Le message a encrypter est :%s et le resultat est: %s\n", message, decoded);
            printf("La cle secrete: (%ld, %ld) et publique: (%ld, %ld)\n", s, n, u, n);
            print_long_vector(crypted, len); 
        }
        printf("Decoded: %s\n", decoded);  
        free(decoded);
        free(crypted);
    }
    return 0;

}
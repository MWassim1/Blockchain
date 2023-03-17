#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "../../Partie3/Exercice5/exercice5.h"
#include "../../Partie4/Exercice6/exercice6.h"
#include "exercice7.h"

int main(){
    
    /*Testing str_to_hash*/
    unsigned char * s= (unsigned char *)str_to_hash(" Rosetta_code ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH ; i ++){
        printf ( "%02x"  , s[ i ]) ;
    }
    putchar ('\n');
    const char * s1= " Rosetta_code " ;
    unsigned char * d =SHA256((const unsigned char*)s1,strlen(s1),0);
    int i ;
    for ( i = 0; i < SHA256_DIGEST_LENGTH ; i ++){
        printf ( "%02x"  , d [ i ]) ;
    }
    putchar ('\n');
    free(s);
    /*Creation Block*/
    int e = 2;
    Block* b1 = create_block_test(NULL, e);
    Block* b2 = create_block_test(b1->hash, e);
    char *c1 =  block_to_str(b1) ;char *c2 = block_to_str(b2) ; 
    printf("b1 :\n %s \n %d\n",c1, verify_block(b1,e));
    printf("b2 :\n %s \n %d\n", c2, verify_block(b2,e));
    
    //Manipulation fichier
    write_file_block("block_b1",b1);
    Block* b3 = read_file_block("block_b1",e);
    char *c3 =  block_to_str(b3);
    printf("b3 : \n %s \n",c3);

    // Test fonction 
    time_compute_proof_of_work(b1);

    //Liberation de la memoire
    delete_block(b3);
    delete_block(b1);
    delete_block(b2);
    free(c3);
    free(c2);
    free(c1);
    
    return 0;
}

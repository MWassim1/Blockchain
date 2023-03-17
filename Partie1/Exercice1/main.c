#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../Exercice1/exercice1.h"

int main(){

    /* Q.2 */
    clock_t temps_initial = clock () ; 
    for (int i = 0 ; i < 64505; i ++){
        if(is_prime_naive(i)){
            printf("%d\n",i);
        }
    }
    clock_t temps_final = clock () ;
    printf("%f\n",(( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC);
    

    /* Q.5*/
    float temps_r1 , temps_r2 ; 
    FILE *f = fopen("calcul_temps.txt","w");

    for (int i = 1000; i <50000; i +=500){
        temps_initial = clock () ;
        modpow_naive(3,i,10);
        temps_final = clock () ;
        temps_r1 =(( double ) ( temps_final - temps_initial )) / CLOCKS_PER_SEC;

        temps_initial = clock () ;
        modpow(3,i,10);
        temps_final = clock () ;
        temps_r2 = (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC;
        fprintf(f,"%d %f %f\n",i,temps_r1,temps_r2);
    }


    fclose(f);
    

    /* Q.8 */
    srand(time(NULL));
    printf("%ld\n",random_prime_number(2,4,2)); 
    
    return 0 ;
}

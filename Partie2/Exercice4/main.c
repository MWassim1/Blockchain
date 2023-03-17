#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../Exercice3/exercice3.h"
#include "exercice4.h"

int main() {
    srand(time(NULL));
    /*NB : le nombre de candidats doit être inférieur ou égal au nombre de voteurs */
    generate_random_data(1000,5);

    return 0;
}
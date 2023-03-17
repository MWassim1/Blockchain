#!/bin/bash
ex1=Partie1/Exercice1
ex2=Partie1/Exercice2
ex3=Partie2/Exercice3
ex4=Partie2/Exercice4
ex5=Partie3/Exercice5
ex6=Partie4/Exercice6
ex7=Partie5/Exercice7
ex8=Partie5/Exercice8
ex9=Partie5/Exercice9

PS3='Choisissez un exercice :'
options=("ex1" "ex2" "ex3" "ex4" "ex5" "ex6" "ex7" "ex8" "ex9" "Quitter")
select opt in "${options[@]}"
do
    case $opt in
        "ex1")
            $ex1/main
            break
            ;;
        "ex2")
            $ex2/main
            break
            ;;
        "ex3")
            $ex3/main
            break
            ;;
        "ex4")
            $ex4/main
            break
            ;;
        "ex5")
            $ex5/main
            break
            ;;
        "ex6")
            $ex6/main
            break
            ;;
        "ex7")
            $ex7/main
            break
            ;;
        "ex8")
            $ex8/main
            break
            ;;
        "ex9")
            $ex9/main
            break
            ;;
        "Quitter")
            break
            ;;
        *) echo "invalid option $REPLY";;
    esac
done

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../Partie1/Exercice1/exercice1.h"
#include "../../Partie1/Exercice2/exercice2.h"
#include "../../Partie2/Exercice3/exercice3.h"
#include "../../Partie2/Exercice4/exercice4.h"
#include "../../Partie3/Exercice5/exercice5.h"
#include "../../Partie4/Exercice6/exercice6.h"
#include "../../Partie5/Exercice7/exercice7.h"
#include "exercice8.h"

CellTree* create_node(Block* b){
    CellTree* node = (CellTree*) malloc(sizeof(CellTree));
    node -> block = b;
    node -> father = NULL;
    node -> firstChild = NULL;
    node -> nextBro = NULL;
    node -> height = 0;
    return node;
}

int update_height(CellTree* father, CellTree* child){
    if(father->height < (child->height +1)){
        father->height = (child->height +1);
        return 1;
    }
    return 0;
}

void add_child(CellTree* father, CellTree* child){
    CellTree* tmp = father;
    child->father = father;
    if(tmp->firstChild){
        while(tmp->nextBro){
            tmp->nextBro = tmp->nextBro->nextBro;
        }
        tmp->nextBro = child;
    }
    else{
        tmp->firstChild = child;
    }
    update_height(father,child);
    while(father->father){
        update_height(father->father, child->father);
        father = father->father;
        child = child->father;
    }
}

void print_tree(CellTree* tree){
    /*supposition : ct n'a pas de father*/
    if(tree){
        printf("%s \t %d \n", tree->block->hash, tree->height);
    }
    else{
        printf("NULL\n");
    }
    if(tree->firstChild){
        print_tree(tree->firstChild);
    }
    if(tree->nextBro){
        print_tree(tree->nextBro);
    }
}

void delete_node(CellTree* node){
    delete_block(node->block);
    free(node);
}

void delete_tree(CellTree* tree){
    if(tree->firstChild){
        delete_tree(tree->firstChild);
    }
    if(tree->nextBro){
        delete_tree(tree->nextBro);
    }
    delete_node(tree);
}

CellTree* highest_child(CellTree* cell){
    if(cell == NULL){
        return NULL;
    }
    int max_height;
    CellTree* tmp = cell;
    if(cell->firstChild){
        tmp = cell->firstChild;
        max_height = cell->firstChild->height;
    }
    else{
        return NULL;
    }
    CellTree *tmp2 = cell->nextBro;
    while(tmp2){
        if(cell->nextBro->height > max_height){
            tmp = cell->nextBro;
            max_height = cell->nextBro->height;
        }
        tmp2= tmp2->nextBro;
    }
    return tmp;
}

CellTree* last_node(CellTree* tree){
    CellTree* tmp = tree;
    while(tmp->height != 0){
        tmp = highest_child(tmp);
    }
    return tmp;
} 

CellProtected  * fusion_liste(CellProtected * l1 , CellProtected * l2){
    if(l1 == NULL){
        return l2;
    }
    if(l2 == NULL){
        return l1;
    }
    CellProtected * tmp2 = l2 ;
    while(tmp2){
        insert_cell_protected(&l1, tmp2->data);
        tmp2 = tmp2->next;
    }
    return l1 ;
}

CellProtected* liste_declaration_block(CellTree* tree){
    CellProtected* cp = create_cell_protected(tree->block->votes->data);
    CellProtected * tmp2 = tree->block->votes->next ; 
    while(tmp2){
        insert_cell_protected(&(cp), tmp2->data);
        tmp2 = tmp2->next;
    }
    CellTree* tmp = highest_child(tree);
    while(highest_child(tmp)!=NULL){
        cp = fusion_liste(cp, tmp->block->votes);
        tmp = highest_child(tmp);
    }
    cp = fusion_liste(cp, tmp->block->votes);
    return cp;
}
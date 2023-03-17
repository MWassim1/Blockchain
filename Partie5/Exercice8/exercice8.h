#ifndef EXERCICE8_H
#define EXERCICE8_H

typedef struct block_tree_cell {
    Block * block ;
    struct block_tree_cell * father ;
    struct block_tree_cell * firstChild ;
    struct block_tree_cell * nextBro ;
    int height ;
} CellTree ;

CellTree* create_node(Block* b);
int update_height(CellTree* father, CellTree* child);
void add_child(CellTree* father, CellTree* child);
void print_tree(CellTree* ct);
void delete_node(CellTree* node);
void delete_tree(CellTree* tree);
CellTree* highest_child(CellTree* cell);
CellTree* last_node(CellTree* tree);
CellProtected  * fusion_liste(CellProtected * l1 , CellProtected * l2);
CellProtected* liste_declaration_block(CellTree* tree);

#endif
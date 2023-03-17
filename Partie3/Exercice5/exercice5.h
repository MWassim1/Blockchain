#ifndef EXERCICE5_H
#define EXERCICE5_H

/*Structures fournies*/
typedef struct cellKey {
    Key* data ;
    struct cellKey* next ;
} CellKey;

typedef struct cellProtected {
    Protected* data ;
    struct cellProtected* next ;
} CellProtected;

CellKey* create_cell_key(Key* key);
CellKey* insert_cell_key(CellKey* LCK, Key* data);
CellKey* read_public_keys(char* nomFic);
void print_list_keys(CellKey* LCK);
void delete_cell_key(CellKey* c);
void delete_list_keys(CellKey* LCK);

CellProtected* create_cell_protected(Protected* pr);
void insert_cell_protected(CellProtected** LCP, Protected* pr);
CellProtected* read_protected(char* nomFic);
void print_list_protected(CellProtected* LCP);
void delete_cell_protected(CellProtected* cp);
void delete_list_protected(CellProtected* LCP);
CellProtected  *fusion_liste(CellProtected * l1 , CellProtected * l2);

#endif


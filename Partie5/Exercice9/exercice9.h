#ifndef EXERCICE9_H
#define EXERCICE9_H

void submit_vote(Protected* p);
void create_block(CellTree* tree, Key* author, int d);
void add_block(int d, char* name);
CellTree* read_tree(int d);
Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV);

#endif
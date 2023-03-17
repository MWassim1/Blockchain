#ifndef EXERCICE7_H
#define EXERCICE7_H

typedef struct block {
    Key * author ;
    CellProtected * votes ;
    unsigned char * hash ;
    unsigned char * previous_hash ;
    int nonce ;
} Block;

void write_file_block(char* nomFic, Block* b);
Block* read_file_block(char* nomFic,int d );
char* block_to_str(Block* block);
char * str_to_hash(char *str );
void compute_proof_of_work(Block *B, int d);
int verify_block(Block* B, int d);
void time_compute_proof_of_work(Block* B);
void delete_block(Block* B);
Block* create_block_test(unsigned char * previous_hash, int d);
#endif

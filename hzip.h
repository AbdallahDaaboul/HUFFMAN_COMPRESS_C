#include "huffman_node.h"

#define EOF_LABEL 256
//Count the number of byte occurences in a file and add a special code for EOF
void compter_occurences(FILE *f, unsigned int distrib[]);
void compress(char *fin, char *fout);
void decompress(char *fin, char *fout);

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "babfiles.h"


typedef struct charTree{
  unsigned int data;
  unsigned int weight;
  struct charTree * left; 
  struct charTree * right;   
} * huffmanTree;


// Tree functions
huffmanTree createNode(unsigned int w, huffmanTree l, huffmanTree r);
huffmanTree createLeaf(unsigned int w, unsigned int c);
huffmanTree addTree(huffmanTree t1, huffmanTree t2);
void freeTree(huffmanTree t);
int isLeafcharTree(huffmanTree t);
void printTree(huffmanTree t);
void printTreeWithWeight(huffmanTree t);

//return the key (e.g. the weight) of a node
int key(huffmanTree t);

/* Build Huffmann Tree */

// Build a tree from a set of character distribution
huffmanTree construire_arbre_codes(unsigned int *distrib);

// Code structure
typedef struct _un_code
{
  unsigned long val;    // value of the code
  unsigned int val_len; // numbre of bit used
} Un_code;

//Build a code table from the Huffmann tree  
void creation_table_codes(huffmanTree arbre_codes, Un_code * table_code);

//Write tree to file
void ecrire_arbre(BAB_FILE *f, huffmanTree arbre_codes);
//Read tree from file
void restaurer_arbre(BAB_FILE *f, huffmanTree *parbre_codes);

//Read a letter from a file
unsigned long restaurer_lettre(BAB_FILE *f, huffmanTree pn);

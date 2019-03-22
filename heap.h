#ifndef __HEAP__
#define __HEAP__
#include <stddef.h>

/* Hypothesis data in heap has functions key.*/
#include "huffman_node.h"
typedef huffmanTree struct_t;

#define MAX_CAP 257

typedef struct t_heap{
  size_t size;
  struct_t tab[MAX_CAP];
} Heap;


Heap * createEmptyHeap();
size_t size(Heap * h);
void printHeap(Heap * h,void (*f)(struct_t));
void insert (Heap * h, struct_t e);
struct_t extractMin(Heap * h);
void printHeapArray(Heap * h);

#endif

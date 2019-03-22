#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "heap.h"


Heap * createEmptyHeap()
{
  Heap * h;
  h = (Heap *) malloc (sizeof(Heap));
  h->size = 0;
  return h;
}

size_t size(Heap * h)
{
  return h->size;
}


int root(void)
{
  return 1;
}

int hasFather(int i)
{  
  return i != root();
}

int leftSon(int i)
{
  return 2 * i;
}

int rightSon(int i)
{
  return 2 * i + 1; 
}

int father(int i)
{
  assert(i > 1);
  return i/2;
}

int isNode(Heap * h , int i) 
{ 
  return i <= size(h) ;
}

int hasLeftSon ( Heap *h , int i ) 
{
  return isNode (h , leftSon(i)) ;
}

int hasRightSon ( Heap *h , int i ) 
{
  return isNode (h , rightSon(i)) ;
}

int isLeaf(Heap * h, int i)
{
  return ! hasLeftSon(h,i); 
}


void printHeapRec(Heap * h, int i, void (*f)(struct_t) )
{ 
  if(i > size(h))
    return;
  if(isLeaf(h,i))
    {
      for(int j = 1; j<= i/2; j++)
	printf("_");
      f(h->tab[i]);
    }
  else 
    {
      for(int j = 1; j<= i/2; j++)
	printf("_");
      f(h->tab[i]);
      printHeapRec(h,leftSon(i),f);
      if (hasRightSon(h,i))
	printHeapRec(h,rightSon(i),f);
    }
}


void printHeap(Heap * h,void (*f)(struct_t))
{
  if (size(h) == 0)
    printf("Tas vide");
  else
    {
      printHeapRec(h,root(),f); 
      printf("\n");
    }
}


void bubbleUp(Heap * h, int i)
{
  if(!hasFather(i))
    return;
  else
    {
      int dadIndex = father(i);
      if(key(h->tab[i]) < key(h->tab[dadIndex]))
	{
	  struct_t tmp = h->tab[i];
	  h->tab[i] = h->tab[dadIndex];
	  h->tab[dadIndex] = tmp;
	  bubbleUp(h,dadIndex);
	}
    }
}

void printHeapArray(Heap * h)
{
  if (size(h) == 0)
    printf("Tas vide");
  else
    {
      for(int i = 1 ; i<= size(h);i++)
	printf("tab[%d] = %d \n",i, key(h->tab[i]));
    }
}


void insert (Heap * h, struct_t e)
{
  h->size++;
  h->tab[h->size] = e;
  bubbleUp(h,h->size);
}

void bubbleDown(Heap * h, int i)
{
  if(isLeaf(h,i))
    return;
  else
    {
      int l_key = key(h->tab[leftSon(i)]);
      if(hasRightSon(h,i))
	{
	  int r_key = key(h->tab[rightSon(i)]);
	  if(l_key > r_key)
	    {
	       struct_t tmp = h->tab[i];
	       h->tab[i] = h->tab[rightSon(i)];
	       h->tab[rightSon(i)] = tmp;
	       bubbleDown(h,rightSon(i));
	       return;
	    }
	}
      if(key(h->tab[i]) > l_key)
	{
	  struct_t tmp = h->tab[i];
	  h->tab[i] = h->tab[leftSon(i)];
	  h->tab[leftSon(i)] = tmp;
	  bubbleDown(h,leftSon(i));
	  return;
	}
    }
}

struct_t extractMin(Heap * h)
{
  struct_t tmp = h->tab[root()];
  h->tab[root()] = h->tab[size(h)];
  h->tab[size(h)] = tmp;
  h->size--;
  bubbleDown(h,root());
  return tmp;
}

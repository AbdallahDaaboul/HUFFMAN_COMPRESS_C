#include "huffman_node.h"
#include <assert.h>

huffmanTree createNode(unsigned int w,huffmanTree l, huffmanTree r)
{
  huffmanTree new_node=(huffmanTree)malloc(sizeof(struct charTree));
  new_node->data=0;
  new_node->weight=w;
  new_node->left=l;
  new_node->right=r;
  return new_node;
}

huffmanTree createLeaf(unsigned int w, unsigned int c)
{
  huffmanTree new_node=(huffmanTree)malloc(sizeof(struct charTree));
  new_node->data=c;
  new_node->weight=w;
  new_node->left=NULL;
  new_node->right=NULL;
  return new_node;
}

void freeTree(huffmanTree t)
{
	if (t->left!=NULL)
		freeTree(t->left);
	if (t->right!=NULL)
		freeTree(t->right);
	free(t);

}

huffmanTree addTree(huffmanTree t1, huffmanTree t2)
{
  if (t1->weight < t2->weight)
  	  return createNode(t1->weight+t2->weight,t1,t2);
  else
  	  return createNode(t1->weight+t2->weight,t2,t1);
}

int isLeafcharTree(huffmanTree t)
{
  assert(t != NULL);
  return (t->left == NULL && t->right == NULL);
}

//0:right 1:left
void  printWhiteSpaces(int b,int pos)
{
  int i;
  if(b != 0)
    {
      for(i=0; i<b; i++) 
	printf(" ");
      if(pos) 
	printf("\\");
      else
	printf("/");
    }
}

void printTreeReal(huffmanTree t,int b, int pos)
{
  if(t ==NULL)
    printf("\n");
  else
    {
      if(isLeafcharTree(t))
	{
	  printWhiteSpaces(b,pos);
	  if(t->data != 256)
	    printf("%c\n",t->data);
	  else
	    printf("eof\n");
	}
      else
	{
	  printTreeReal(t->right,b+2,0);
	  printWhiteSpaces(b,pos);
	  printf("*\n");
	  printTreeReal(t->left,b+2,1);
	}
    }
}


void printTreeWithWeightReal(huffmanTree t,int b, int pos)
{
  if(t ==NULL)
    printf("\n");
  else
    {
      if(isLeafcharTree(t))
	{
	  printWhiteSpaces(b,pos);
	  switch(t->data)
	    {
	    case '\n': printf("\\n(%d)\n",t->weight); break;
	    case '\t': printf("\\t(%d)\n",t->weight); break;
	    case ' ' : printf("\" \"(%d)\n",t->weight); break;
	    case 256 : printf("EOF(%d)\n",t->weight); break;
	    default:printf("%c(%d)\n",t->data,t->weight);
	    }
	}
      else
	{
	  printTreeWithWeightReal(t->right,b+4,0);
	  printWhiteSpaces(b,pos);
	  printf("(%d)\n",t->weight);
	  printTreeWithWeightReal(t->left,b+4,1);
	}
    }
}
void printTree(huffmanTree t)
{
  printTreeReal(t,0,0);
}

void printTreeWithWeight(huffmanTree t)
{
    printTreeWithWeightReal(t,0,0);
}

int key(huffmanTree t)
{
  return t->weight;
}


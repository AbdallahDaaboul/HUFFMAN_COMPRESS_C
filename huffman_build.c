#include "huffman_node.h"
#include "heap.h"
#include <assert.h>


huffmanTree construire_arbre_codes(unsigned int *distrib)
{

  Heap* tas=createEmptyHeap();
  for (int i = 0; i < 257; i++)
    if (distrib[i]!=0)
      insert(tas,createLeaf(distrib[i],i));

  while(tas->size!=1){
    if (tas->size==2)
      return addTree(extractMin(tas),extractMin(tas));
    insert(tas,addTree(extractMin(tas),extractMin(tas)));
  }
  return NULL;
}

void creation_table_codes(huffmanTree arbre_codes, Un_code * table_code)
{
		//printf("\n %ld\t%d\n",table_code[0].val,table_code[0].val_len );
		unsigned long v;
		unsigned int lv;
    if (arbre_codes==NULL) {
      printf("null\n" );
    }
    else{
  		if (arbre_codes->left!=NULL)
  		{
  			table_code[0].val=2*table_code[0].val;
  			table_code[0].val_len++;
  			v=table_code[0].val;
  			lv=table_code[0].val_len;

  			creation_table_codes(arbre_codes->left,table_code);

  			table_code[0].val=v;
  			table_code[0].val_len=lv;

  			table_code[0].val=table_code[0].val+1;
  			creation_table_codes(arbre_codes->right,table_code);

  		}
  		else{
  			table_code[arbre_codes->data].val=table_code[0].val;
        table_code[arbre_codes->data].val_len=table_code[0].val_len;
      }
    }
}

void ecrire_arbre(BAB_FILE *f, huffmanTree arbre_codes)
{
  int a=0;
  int b=1;
  if (arbre_codes!=NULL) {
    if (arbre_codes->left==NULL){
      bab_fwrite(&a,1, f);
      bab_fwrite(&(arbre_codes->data),9,f);
    }
    else{
      bab_fwrite(&b,1, f);

    }

    ecrire_arbre( f,  arbre_codes->left);
    ecrire_arbre(f,  arbre_codes->right);
  }
}

void restaurer_arbre(BAB_FILE *f, huffmanTree *parbre_codes)
{
  unsigned long data = 0;
  huffmanTree pn = createLeaf(0,0);

  *parbre_codes = pn;
  if (bab_fread(&data, 1, f) == 0)
    {
      fprintf(stderr,"Impossible de lire l'arbre de codage\n");
      exit(1);
    }

  if (data & 1)
    {
      restaurer_arbre(f, &(pn->left));
      restaurer_arbre(f, &(pn->right));
    }
  else
    {
      pn->data = 0;
      bab_fread(&(pn->data), 9, f);
      pn->data &= 0x1FF;
      pn->left = NULL;
      pn->right = NULL;
    }
}


unsigned long restaurer_lettre(BAB_FILE *f, huffmanTree pn)
{
  huffmanTree tmp=pn;
  while (tmp->left!=0){
    char c = 0;

    bab_fread(&c, 1, f);
    c=c&1;
    if (c==1)
      tmp=tmp->right;
    else
      tmp=tmp->left;
  }
  return tmp->data;
}

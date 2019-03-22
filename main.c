#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "hzip.h"


/*************************************************************************/
/*                     Fonctions de test                                 */
/*************************************************************************/
void test_compter_occurences(char * fin)
{
  unsigned int distrib[257];
  FILE* ffin = fopen(fin,"r");
  int i;


  compter_occurences(ffin,distrib);
  for(i = 0; i < 256; i++)
    {
      if(distrib[i] != 0)
	     {
	        printf("\"%c\" : %d\n",i,distrib[i]);
	     }
    }
  printf("EOF : %d \n", distrib[i]);
  fclose(ffin);
}

void test_construire_arbre_codes(char * fin)
{
  unsigned int distrib[257];
  FILE* ffin = fopen(fin,"r");
  huffmanTree arbre_codes;

  compter_occurences(ffin, distrib);
  // construction de l'arbre de codage
  arbre_codes = construire_arbre_codes(distrib);
  printTreeWithWeight(arbre_codes);
  fclose(ffin);
}

void printCode(Un_code c)
{
  int i;
  for (i = 0; i < c.val_len; i++)
    {
      printf("%lu",c.val % 2);
      c.val = c.val / 2;
    }
}

void test_construire_tables_codes(char * fin)
{
  unsigned int distrib[257];
  FILE* ffin = fopen(fin,"r");
  huffmanTree arbre_codes;
  Un_code tab_codes[257];

  int i;

  compter_occurences(ffin, distrib);
  // construction de l'arbre de codage
  arbre_codes = construire_arbre_codes(distrib);
  printTreeWithWeight(arbre_codes);
  creation_table_codes(arbre_codes, tab_codes);

  for (i = 0; i < 257; i++)
    {
      if(distrib[i] > 0)
  	{
  	  switch(i)
  	    {
  	    case '\n': printf("\\n : "); printCode(tab_codes[i]); break;
  	    case '\t': printf("\\t : "); printCode(tab_codes[i]); break;
  	    case ' ' : printf("\" \" : ");printCode(tab_codes[i]); break;
  	    case 256 : printf("EOF : "); printCode(tab_codes[i]); break;
  	    default:printf("%c : ",i); printCode(tab_codes[i]);
  	    }
	  printf(" \n");
  	}

    }
  fclose(ffin);
}

void test_save_arbre(char * fin)
{
  unsigned int distrib[257];
  FILE* ffin = fopen(fin,"r");
  huffmanTree arbre_codes;
  huffmanTree test_arbre_codes;
  BAB_FILE *f_dst;

  compter_occurences(ffin, distrib);
  // construction de l'arbre de codage
  arbre_codes = construire_arbre_codes(distrib);
  printTreeWithWeight(arbre_codes);

  f_dst = bab_fopen("out.txt", "w");
  ecrire_arbre(f_dst, arbre_codes);
  freeTree(arbre_codes);
  bab_fclose(f_dst);

  printf("**********************************\n");
  //Restore
  f_dst = bab_fopen("out.txt", "r");

  restaurer_arbre(f_dst, &test_arbre_codes);
  printTreeWithWeight(test_arbre_codes);
  freeTree(test_arbre_codes);
  bab_fclose(f_dst);

  fclose(ffin);
}
/*************************************************************************/
/*                     programme principal                               */
/*************************************************************************/

int main(int argc, char *argv[])
{
  char *fin;
  char fout[32];


  if ((argc < 3) || (argc > 4))
  {
    fprintf(stderr,"Usage : hzip [-c/-d/-t] fichier_entre [fichier_sortie]\n");
    exit (-1);
  }

  fin = argv[2];
  if (!strcmp(argv[1],"-t"))
  {
    //test_compter_occurences(fin);
    //test_construire_arbre_codes(fin);
    test_construire_tables_codes(fin);
    test_save_arbre(fin);
  }
  else if (!strcmp(argv[1],"-c"))
    {
      if(argc == 3)
	{
	  sprintf(fout, "%s.hz", fin);
	}
      else
	{
	  strcpy(fout, argv[3]);
	}
      compress(fin, fout);
    }
  else if(!strcmp(argv[1], "-d"))
    {
      if(argc == 3)
	{
	  strcpy(fout, argv[2]);
	  fout[strlen(fout) - 3] = '\0';
	}
      else
	{
	  strcpy(fout, argv[3]);
	}
      decompress(fin, fout);
    }
  else
    {
      fprintf(stderr,"Argument invalide\n");
      exit (-1);
    }
  return(0);
}

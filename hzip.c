#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "hzip.h"


void compter_occurences(FILE *f, unsigned int distrib[])
{
  for (int i = 0; i < 256; i++)
    distrib[i]=0;

  distrib[256]=1;
  int a=0;
  while(a!=EOF){
    a=fgetc(f);
    if (a!=EOF)
      distrib[a]++;
  }

}



/*************************************************************************/
/*                     fonction de compression                           */
/*************************************************************************/

void compress(char *fin, char *fout)
{
    unsigned int distrib[257];
    FILE * i=fopen(fin, "r");
    BAB_FILE * f=bab_fopen(fout, "w");

  /****************CREER Tab-Codes et Le BABFILE****************/
    compter_occurences(i, distrib);
    huffmanTree arbre_codes = construire_arbre_codes(distrib);
    printTreeWithWeight(arbre_codes);
    Un_code tab_codes[257];

    for (size_t z = 0; z < 257; z++) {
      tab_codes[z].val=0;
      tab_codes[z].val_len=0;
    }

    creation_table_codes(arbre_codes,tab_codes);
    ecrire_arbre(f,  arbre_codes);
  /****************AJOUTER DANS LE BABFILE****************/
    int a=0;
    rewind(i);

    while(a!=EOF){
      a=fgetc(i);

      int* code = (int *)malloc(tab_codes[a].val_len * sizeof(int));
      int l = tab_codes[a].val;
      for (size_t j = 0; j < tab_codes[a].val_len; j++) {
        //printf("%ld\n",tab_codes[a].val%2 );
        code[tab_codes[a].val_len-j-1] = l%2;
        l/=2;
      }

      for (size_t k = 0; k < tab_codes[a].val_len; k++) {
        //printf("%d", code[k]);
        bab_fwrite(&(code[k]),1, f);
      }

    }

    int* code = (int *)malloc(tab_codes[256].val_len * sizeof(int));
    int l = tab_codes[256].val;
    for (size_t j = 0; j < tab_codes[256].val_len; j++) {
      //printf("%ld\n",tab_codes[a].val%2 );
      code[tab_codes[256].val_len-j-1] = l%2;
      l/=2;
    }
    for (size_t k = 0; k < tab_codes[256].val_len; k++) {

      bab_fwrite(&(code[k]),1, f);
    }

    bab_fclose(f);
    fclose(i);
    freeTree(arbre_codes);
    free(code);
}

/*************************************************************************/
/*                     fonction de decompression                         */
/*************************************************************************/

  void decompress(char *fin, char *fout)
  {
    int c;
    BAB_FILE *f_src;
    FILE *f_dst;
    huffmanTree arbre_codes;

    // ouverture du fichier binaire fin

    f_src = bab_fopen(fin, "r");
    if ( f_src == NULL)
      {
        fprintf(stderr,"Impossible d ouvrir le fichier source %s\n", fin);
        exit(1);
      }

    // restauration de l arbre de codage

    restaurer_arbre(f_src, &arbre_codes);
    // ouverture du fichier de sortie

    f_dst = fopen(fout, "w");
    if ( f_dst == NULL)
      {
        fprintf(stderr,"Impossible d ouvrir le fichier source %s\n", fout);
        exit(1);
      }

    // restauration des donnees

    while ( (c = restaurer_lettre(f_src, arbre_codes)) != EOF_LABEL)
      {
        fputc(c, f_dst);
      }

    // destruction de l'arbre de codage

    freeTree(arbre_codes);

    // fermeture du fichier binaire fin

    bab_fclose(f_src);

    // fermeture du fichier fout

    fclose(f_dst);
  }

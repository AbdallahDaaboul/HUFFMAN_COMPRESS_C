/* BAB for Bit a BIT*/
#ifndef _COMPRESS
#define _COMPRESS

#include<stdio.h>

typedef struct _BAB_FILE
	{
	FILE *f;
	unsigned char rwbuff;
	unsigned int rwpointer;
	unsigned char mode;
	} BAB_FILE;

/* fonction d'ouverture de fichier
attention seuls les modes r, w et a sont autotisés*/

BAB_FILE * bab_fopen(const char *path, const char *mode);

/* vide le buffer et ferme le fichier*/
int bab_fclose(BAB_FILE *babf);

/* lit bsize bits dans le fichier bab_stream deja ouvert */
/* les octets lus seront allignes sur les bits de poid faible */
/* attention la valeur des bits non demandes est quelconque */
/* pensez a faire un mask data &= (-1) >> (data_size - bsize) */
/* du premier octet pointe par ptr */
int bab_fread(void *ptr, int bsize, BAB_FILE *babf);

/* ecrit bsize bits dans le fichier bab_stream deja ouvert */
/* les octets seront ecrits allignes sur les bits de poids faible */
/* du premier octet pointe par ptr */
int bab_fwrite(const  void  *ptr, int bsize, BAB_FILE *babf);

#endif

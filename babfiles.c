#include<stdlib.h>
#include"babfiles.h"

BAB_FILE * bab_fopen(const char *path, const char *mode)
	{
	BAB_FILE *babf;

	babf=malloc(sizeof(BAB_FILE));
	babf->rwpointer=0;
	babf->rwbuff=0;

	if (*mode =='r')
		{
		if (!(babf->f = fopen(path, mode)))
			{
			fprintf(stderr, "impossible d ouvrir en lect le fichier %s\n", path);
			exit(1);
			}
		babf->mode='r';
		fread(&(babf->rwbuff), 1, 1, babf->f);
		return babf;
		}
	else if ((*mode=='w') || (*mode=='a'))
		{
		if (!(babf->f = fopen(path, mode)))
			{
			fprintf(stderr, "impossible d'ouvrir le fichier %s\n", path);
			exit(1);
			}
		babf->mode='w';
		return babf;
		}
	return NULL;
	}

int bab_fclose(BAB_FILE *babf)
	{
	int retvalue;
	if ((babf->mode == 'w') && (babf->rwpointer))
		fwrite(&(babf->rwbuff), 1, 1, babf->f);
	retvalue = fclose(babf->f);
	free(babf);
	return retvalue;
	}

int bab_fread(void *ptr, int bsize, BAB_FILE *babf)
	{
	int cur_bsize = bsize;
	int cur_wpointer = 0;

	if (!babf)
		return 0;

	// mise a 0 de la dest
	*(unsigned char *) ptr = 0;

	while (cur_bsize > 0) // il reste quelque chose à lire
		{
		// lecture si buffer vide
		if (babf->rwpointer >= 8) 
			{
			fread(&(babf->rwbuff), 1, 1, babf->f);
			babf->rwpointer = 0;
			}

		// calcul du nombre effectif de bits transferes
		// depend du nombre de bits deja ecrits dans la dest
		// du nombre de bits restant a ecrire dans le buffer
		// du nombre de bits restant a copier
		int eff_bits_copy;
		if ((8 - cur_wpointer) < cur_bsize) // moins de place dans dest que bsize
			{
			if (cur_wpointer < babf->rwpointer) eff_bits_copy = 8-babf->rwpointer;
			else eff_bits_copy = 8 - cur_wpointer;
			}
		else
			{
			if (cur_bsize > (8-babf->rwpointer)) eff_bits_copy = 8-babf->rwpointer;
			else eff_bits_copy = cur_bsize;
			}

		// copie
		*(unsigned char *) ptr |= (babf->rwbuff >> babf->rwpointer) << cur_wpointer;

		// mise a jour des pointeurs 
		babf->rwpointer += eff_bits_copy;
		cur_wpointer += eff_bits_copy;
		if (cur_wpointer >= 8 )
			{
			cur_wpointer = 0;
			ptr ++;
			*(unsigned char *) ptr = 0;
			}
		cur_bsize -= eff_bits_copy;
		}
	return bsize;
	}

int bab_fwrite(const  void  *ptr, int bsize, BAB_FILE *babf)
	{
	int cur_bsize = bsize;
	int cur_rpointer = 0;

	if (!babf)
		return 0;
	while (cur_bsize > 0) // il reste quelque chose à ecrire
		{
		// calcul du nombre effectif de bits transferes
		// depend du nombre de bits deja ecrits dans la dest
		// du nombre de bits restant a ecrire dans le buffer
		// du nombre de bits restant a copier
		int eff_bits_copy;
		if ((8 - cur_rpointer) < cur_bsize) // moins de place dans dest que bsize
			{
			if (cur_rpointer < babf->rwpointer) eff_bits_copy = 8-babf->rwpointer;
			else eff_bits_copy = 8 - cur_rpointer;
			}
		else
			{
			if (cur_bsize > (8-babf->rwpointer)) eff_bits_copy = 8-babf->rwpointer;
			else eff_bits_copy = cur_bsize;
			}

		// copie
		babf->rwbuff |= (*(unsigned char *) ptr >> cur_rpointer) << babf->rwpointer;

		// mise a jour des pointeurs 
		babf->rwpointer += eff_bits_copy;
		cur_rpointer += eff_bits_copy;
		if (cur_rpointer >= 8 )
			{
			cur_rpointer = 0;
			ptr ++;
			}
		cur_bsize -= eff_bits_copy;

		// copie effective si buffer plein
		if (babf->rwpointer >= 8) //buffer plein
			{
			fwrite(&(babf->rwbuff), 1, 1, babf->f);
			babf->rwbuff = 0;
			babf->rwpointer = 0;
			}
		}
	return bsize;
	}

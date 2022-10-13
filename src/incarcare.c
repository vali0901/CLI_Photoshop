#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/diverse.h"

//pentru functiile de citire, m reprezinta latimea iar n inaltimea

double **citire_matrice(int m, int n, FILE *f, int rgb)
{
	double **mat = alocare_memorie(m, n, rgb);
	if (mat)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < rgb * m; j++)
				fscanf(f, "%lf", &mat[i][j]);
	return mat;
}

double **citire_matrice_b(int m, int n, FILE *f, int rgb)
{
	double **mat = alocare_memorie(m, n, rgb);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < rgb * m; j++) {
			unsigned char aux;
			fread(&aux, sizeof(unsigned char), 1, f);
			mat[i][j] = aux;
		}
	return mat;
}

double **incarcare(char fisier[], int *l, int *h, int *x1, int *y1, int *x2,
				   int *y2, double **p, int *vmax, int *rgb)
{
	FILE *f = fopen(fisier, "rt");

	if (!f) {
		printf("Failed to load %s\n", fisier);
		if (p)
			p = elim_memorie(*h, p);
		return NULL;
	}
	if (f) {
		//daca in p era salvata alta imagine, o eliminam
		if (p)
			p = elim_memorie(*h, p);
		char tip[2];

		//se citeste tipul imaginii si se retin urmatoarele valori in functie
		//de acesta

		fscanf(f, "%s", tip);
		elim_com(f);

		fscanf(f, "%d%d", l, h);
		elim_com(f);

		if (strcmp(tip, "P2") == 0 || strcmp(tip, "P3") == 0 ||
			strcmp(tip, "P5") == 0  || strcmp(tip, "P6") == 0)
			fscanf(f, "%d", vmax);
		elim_com(f);

		if (strcmp(tip, "P3") == 0 || strcmp(tip, "P6") == 0)
			*rgb = 3;
		else
			*rgb = 1;

		//daca fisierul este binar retinem pozitia pana la care am citit,
		//redeschidem fisierul in mod corespunzator si ne pozitionam unde
		//incepe practic matricea de pixeli

		int poz = ftell(f);
		if (strcmp(tip, "P5") == 0  || strcmp(tip, "P6") == 0) {
			fclose(f);
			FILE *f = fopen(fisier, "rb");
			fseek(f, poz, SEEK_SET);
			p = citire_matrice_b(*l, *h, f, *rgb);
			fclose(f);
		} else {
			p = citire_matrice(*l, *h, f, *rgb);
			fclose(f);
		}
		printf("Loaded %s\n", fisier);

		//aici sunt setate variabilele x1, x2, y1, y2 echivalentul selectiei
		//totale a matricei

		*x1 = *y1 = 0;
		*x2 = *l;
		*y2 = *h;
	}
	return p;
}

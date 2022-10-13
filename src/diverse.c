#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//functia ce incadreaza valoralea rezultata in urma unei operatii de APPLY
//in [vmin, vmax], adica [0, 255]
double clamp(double s, int vmin, int  vmax)
{
	if (s < vmin)
		s = vmin;
	else if (s > vmax)
		s = vmax;
	return s;
}

void interschimbare(int *x, int *y)
{
	int aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

//functie ce citeste toate caracterele pana la capatul liniei, folosita
//in cazul unor comenzi sau parametrii incorecti
void citire_rand(void)
{
	char next_char;
	do {
		scanf("%c", &next_char);
	} while (next_char != '\n');
}

//functie ce elimina comentariile din fisiere
void elim_com(FILE *f)
{
	char c;

	//citim primul caracter diferit de terminatorul de linie
	do {
		fscanf(f, "%c", &c);
	} while (c == '\n');

	//daca acesta este "#" citim comentariul, adica pana la intalnirea "\n"
	// si apoi apelam recursiv functia in cazul in care sunt mai multe
	//comentarii consecutive
	if (c == '#') {
		do {
			fscanf(f, "%c", &c);
		} while (c != '\n');
		elim_com(f);
	} else {
		fseek(f, -1, SEEK_CUR);
	}
}

//pentru alocarea memoriei, am folosit m ca fiind echivalentul latimii
//imaginii, n reprezentand inaltimea, si am ales sa lucrez cu o matrice de tip
//double, pentru aproximari cat mai precise la operatiile ulterioare
double **alocare_memorie(int m, int n, int rgb)
{
	double **mat;
	double **tmp = (double **)malloc(n * sizeof(double *));
	if (!tmp) {
		fprintf(stderr, "eroare alocare malloc\n");
		return NULL;
	}
	//in cazul imaginilor color, se vor aloca 3 * m pozitii, pentru a retine
	//fiecare culoare a pixelului
	for (int i = 0; i < n; i++) {
		tmp[i] = (double *)malloc((rgb * m) * sizeof(double));
		if (!tmp[i]) {
			fprintf(stderr, "eroare alocare malloc\n");
			return NULL;
			for (int j = 0; j < i; j++)
				free(tmp[i]);
		}
	}
	mat = tmp;
	return mat;
}

double **elim_memorie(int n, double **mat)
{
	if (!n)
		return NULL;
	for (int i = 0 ; i < n; i++)
		free(mat[i]);
	free(mat);
	return mat;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/diverse.h"

void save_binar(char fisier[], int l, int h, double **mat,
				int vmax, int rgb)
{
	FILE *f = fopen(fisier, "wb");
	if (f) {
		if (rgb == 3)
			fprintf(f, "P6\n");
		else if (rgb == 1)
			fprintf(f, "P5\n");

		fprintf(f, "%d %d\n%d\n", l, h, vmax);

		for (int i = 0; i < h; i++)
			for (int j = 0; j < rgb * l; j++) {
				unsigned char aux = round(mat[i][j]);
				fwrite(&aux, sizeof(unsigned char), 1, f);
			}

		fclose(f);
	}
}

void save_text(char fisier[], int l, int h, double **mat,
			   int vmax, int rgb)
{
	FILE *f = fopen(fisier, "wt");
	if (f) {
		if (rgb == 3)
			fprintf(f, "P3\n");
		else if (rgb == 1)
			fprintf(f, "P2\n");

		fprintf(f, "%d %d\n%d\n", l, h, vmax);

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < rgb * l; j++) {
				unsigned char aux = round(mat[i][j]);
				fprintf(f, "%hhu ", aux);
			}
			fprintf(f, "\n");
		}
	fclose(f);
	}
}

void salvare(double **p, int l, int h, int vmax, int rgb)
{
	char fisier[100];
	scanf("%s", fisier);
	char next_char;
	//citim primul caracter diferit de spatiu, iar daca acesta este a, se face
	//salvare intr-un fisier text, iar daca este terminator de linie, se face
	//salvare in fisier binar
	do {
		scanf("%c", &next_char);
	} while (next_char == ' ');

	if (next_char == '\n') {
		if (!p) {
			printf("No image loaded\n");
		} else {
			save_binar(fisier, l, h, p, vmax, rgb);
			printf("Saved %s\n", fisier);
		}
	} else if (next_char == 'a') {
		citire_rand();
		if (!p) {
			printf("No image loaded\n");
		} else {
			save_text(fisier, l, h, p, vmax, rgb);
			printf("Saved %s\n", fisier);
		}
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/diverse.h"

//pentru operatia de APPLY am facut cate o functie pentru fiecare efect,
//dar acestea sunt identice, singurul element diferit fiind matricea kernel

double **aplicare_edge(int l, int h, int x1, int y1, int x2, int y2,
					   double **mat, int rgb, int vmax)
{
	double edge[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};

	//setarea dimensiunilor noii matrici, pentru care se aloca memorie

	int tmp_l = x2 - x1;
	int tmp_h = y2 - y1;
	double **tmp = alocare_memorie(tmp_l, tmp_h, rgb);

	for (int i = y1; i < y2; i++)
		for (int j = rgb * x1; j < x2 * rgb; j++) {
			//pentru fiecare element al noii matrici construim o suma si
			//folosim un sw care indica daca elementul a avut sau nu vecini,
			//pentru aplicarea kernelului
			double sum = 0, sw = 1;
			for (int w = 0; w < 3; w++)
				for (int q = 0; q < 3; q++) {
					//conditia pentru verifcarea existentei vecinilor:
					//-cu w-1 se cauta vecinii "de sus in jos", iar indicii
					//ce rezulta trebuie sa fie in [0, h)
					//-acelasi lucru se intampla si cu q-1, dar inmultim cu 3
					//pentru a selecta doar pixelii de aceeasi culoare, altfel
					//spus, ne plimbam din 3 in 3 de la stanga la dreapta
					if (((i + w - 1) < h && (i + w - 1) >= 0) &&
						((j + 3 * (q - 1)) < l * rgb &&
						(j + 3 * (q - 1)) >= 0))
						sum += mat[i + w - 1][j + 3 * (q - 1)] * edge[w][q];
					else
						sw = 0;
				}
			sum = clamp(sum, 0, vmax);

			//daca elementul matricei a avut toti vecinii atunci se rotunjeste
			//rezultatul, altfel se ia valoarea deja existenta in matrice

			if (sw == 1)
				tmp[i - y1][j - rgb * x1] = sum;
			else
				tmp[i - y1][j - rgb * x1] = mat[i][j];
		}

	// apoi reactualizez matricea imaginii intiale cu noile valori
	for (int i = y1; i < y2; i++)
		for (int j = rgb * x1; j < rgb * x2; j++)
			mat[i][j] = tmp[i - y1][j - rgb * x1];

	tmp = elim_memorie(tmp_h, tmp);

	return mat;
}

double **aplicare_sharpen(int l, int h, int x1, int y1, int x2, int y2,
						  double **mat, int rgb, int vmax)
{
	double sharpen[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
	int tmp_l = x2 - x1;
	int tmp_h = y2 - y1;
	double **tmp = alocare_memorie(tmp_l, tmp_h, rgb);

	for (int i = y1; i < y2; i++)
		for (int j = rgb * x1; j < x2 * rgb; j++) {
			double sum = 0, sw = 1;
			for (int w = 0; w < 3; w++)
				for (int q = 0; q < 3; q++) {
					if (((i + w - 1) < h && (i + w - 1) >= 0) &&
						((j + 3 * (q - 1)) < l * rgb &&
						(j + 3 * (q - 1)) >= 0))
						sum += mat[i + w - 1][j + 3 * (q - 1)] * sharpen[w][q];
					else
						sw = 0;
				}

			sum = clamp(sum, 0, vmax);

			if (sw == 1)
				tmp[i - y1][j - rgb * x1] = sum;
			else
				tmp[i - y1][j - rgb * x1] = mat[i][j];
		}

	for (int i = y1; i < y2; i++)
		for (int j = rgb * x1; j < rgb * x2; j++)
			mat[i][j] = tmp[i - y1][j - rgb * x1];

	tmp = elim_memorie(tmp_h, tmp);

	return mat;
}

double **aplicare_blur(int l, int h, int x1, int y1, int x2, int y2,
					   double **mat, int rgb, int vmax)
{
	double blur = 1.0 / 9.0;

	int tmp_l = x2 - x1;
	int tmp_h = y2 - y1;
	double **tmp = alocare_memorie(tmp_l, tmp_h, rgb);

	for (int i = y1; i < y2; i++)
		for (int j = rgb * x1; j < x2 * rgb; j++) {
			double sum = 0, sw = 1;
			for (int w = 0; w < 3; w++)
				for (int q = 0; q < 3; q++) {
					if (((i + w - 1) < h && (i + w - 1) >= 0) &&
						((j + 3 * (q - 1)) < l * rgb &&
						(j + 3 * (q - 1)) >= 0))
						sum += mat[i + w - 1][j + 3 * (q - 1)];
					else
						sw = 0;
				}

			sum *= blur;
			sum = clamp(sum, 0, vmax);

			if (sw == 1)
				tmp[i - y1][j - rgb * x1] = sum;
			else
				tmp[i - y1][j - rgb * x1] = mat[i][j];
		}

	for (int i = y1; i < y2; i++)
		for (int j = rgb * x1; j < rgb * x2; j++)
			mat[i][j] = tmp[i - y1][j - rgb * x1];

	tmp = elim_memorie(tmp_h, tmp);

	return mat;
}

double **aplicare_gaussian_blur(int l, int h, int x1, int y1, int x2,
								int y2, double **mat, int rgb, int vmax)
{
	double gaussian_blur[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
	double value = 0.0625; // == 1/16

	int tmp_l = x2 - x1;
	int tmp_h = y2 - y1;
	double **tmp = alocare_memorie(tmp_l, tmp_h, rgb);

	for (int i = y1; i < y2; i++)
		for (int j = rgb * x1; j < x2 * rgb; j++) {
			double sum = 0, sw = 1;
			for (int w = 0; w < 3; w++)
				for (int q = 0; q < 3; q++) {
					if (((i + w - 1) < h && (i + w - 1) >= 0) &&
						((j + 3 * (q - 1)) < l * rgb &&
						(j + 3 * (q - 1)) >= 0))
						sum += mat[i + w - 1][j + 3 * (q - 1)] *
							   gaussian_blur[w][q];
					else
						sw = 0;
				}

			sum *= value;
			sum = clamp(sum, 0, vmax);

			if (sw == 1)
				tmp[i - y1][j - rgb * x1] = sum;
			else
				tmp[i - y1][j - rgb * x1] = mat[i][j];
		}

	for (int i = y1; i < y2; i++)
		for (int j = rgb * x1; j < rgb * x2; j++)
			mat[i][j] = tmp[i - y1][j - rgb * x1];

	tmp = elim_memorie(tmp_h, tmp);

	return mat;
}

double **aplicare_efect(int l, int h, int x1, int y1, int x2, int y2,
						double **p, int rgb, int vmax)
{
	char next_char, parametru[20] = "";
	int sw = 1;
	scanf("%c", &next_char);
	//pentru cazul in care dupa comanda APPLY nu urmeaza nimic, setam sw 0
	//si afisam (mai jos) mesajul corespunzator.
	if (next_char == '\n')
		sw = 0;
	else
		scanf("%s", parametru);

	if (!p) {
		printf("No image loaded\n");
	} else if (strcmp(parametru, "EDGE") == 0) {
		if (rgb == 1) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double **aux = aplicare_edge(l, h, x1, y1, x2, y2, p, rgb,
												vmax);
			if (aux) {
				p = aux;
				printf("APPLY %s done\n", parametru);
			}
		}
	} else if (strcmp(parametru, "SHARPEN") == 0) {
		if (rgb == 1) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double **aux = aplicare_sharpen(l, h, x1, y1, x2, y2, p,
												   rgb, vmax);
			if (aux) {
				p = aux;
				printf("APPLY %s done\n", parametru);
			}
		}
	} else if (strcmp(parametru, "BLUR") == 0) {
		if (rgb == 1) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double **aux = aplicare_blur(l, h, x1, y1, x2, y2, p, rgb,
												vmax);
			if (aux) {
				p = aux;
				printf("APPLY %s done\n", parametru);
			}
		}
	} else if (strcmp(parametru, "GAUSSIAN_BLUR") == 0) {
		if (rgb == 1) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double **aux = aplicare_gaussian_blur(l, h, x1, y1, x2, y2,
														 p, rgb, vmax);
			if (aux) {
				p = aux;
				printf("APPLY %s done\n", parametru);
			}
		}
	} else {
		if (sw == 0)
			printf("Invalid command\n");
		else
			printf("APPLY parameter invalid\n");
	}
	return p;
}

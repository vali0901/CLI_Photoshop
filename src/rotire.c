#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/diverse.h"

double **rotire_90_dreapta(int *l, int *h, int *x1, int *y1, int *x2, int *y2,
						   double **p, int rgb)
{
	//setarea dimensiunilor noii matrici, tmp_h -> inaltimea, tmp_l -> latimea
	int tmp_h = *x2 - *x1;
	int tmp_l = *y2 - *y1;
	double **tmp = alocare_memorie(tmp_l, tmp_h, rgb);
	if (!tmp)
		return p;
	//cazul in care selectia nu este patratica, deci este selectata intreaga
	//imagine, ceea ce inseamna ca se va crea alta matrice in locul matricei
	//initiale
	if (tmp_h != tmp_l) {
		for (int i = 0; i < *y2; i++)
			for (int j = 0; j < *x2; j++)
				for (int k = 0; k < rgb; k++)
					//aici sunt atribuite valorile matricei, dupa "rotatie"
					tmp[j][(*y2 - i - 1) * rgb + k] = p[i][rgb * j + k];

		p = elim_memorie(tmp_l, p);
		p = tmp;
		//dupa rotire este necesar sa interschimbam dimensiunile
		interschimbare(l, h);
		interschimbare(x1, y1);
		interschimbare(x2, y2);

	} else {
		//pentru selectiile patratice se creeaza matricea tmp corespunzator
		//si valorile optinute dupa "rotatie" sunt puse din nou in matricea
		//initiala a imaginii
		for (int i = *y1; i < *y2; i++)
			for (int j = *x1; j < *x2; j++)
				for (int k = 0; k < rgb; k++)
					tmp[j - *x1][(*y2 - i - 1) * rgb + k] = p[i][rgb * j + k];

	for (int i = *y1; i < *y2; i++)
		for (int j = rgb * (*x1); j < rgb * (*x2); j++)
			p[i][j] = tmp[i - *y1][j - rgb * (*x1)];

	tmp = elim_memorie(tmp_h, tmp);
	}
	return p;
}

double **rotire(int *l, int *h, int *x1, int *y1, int *x2, int *y2, double **p,
				int rgb)
{
	int unghi;
		scanf("%d", &unghi);
	if (!p) {
		printf("No image loaded\n");
	} else {
		//se va efectua rotatia doar daca selectia este patratica sau
		//este selectata toata imaginea (coordonatele sunt in "colturile"
		//imaginii: 0,0,l,h)
		if ((x2 - x1 != y2 - y1) && (x1 != 0 || x2 != l || y1 != 0 || y2 != h))
			printf("The selection must be square\n");
		else
			switch (unghi) {
			case 0:
				printf("Rotated %d\n", unghi);
			break;
			case 90:
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				printf("Rotated %d\n", unghi);
			break;
			case 180:
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				printf("Rotated %d\n", unghi);
			break;
			case 270:
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				printf("Rotated %d\n", unghi);
			break;
			case 360:
				printf("Rotated %d\n", unghi);
			break;
			case -360:
				printf("Rotated %d\n", unghi);
			break;
			case -270:
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				printf("Rotated %d\n", unghi);
			break;
			case -180:
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				printf("Rotated %d\n", unghi);
			break;
			case -90:
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				p = rotire_90_dreapta(l, h, x1, y1, x2, y2, p, rgb);
				printf("Rotated %d\n", unghi);
			break;
			default:
			printf("Unsupported rotation angle\n");
		}
	}
	return p;
}

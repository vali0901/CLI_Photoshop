#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "diverse.h"

double **citire_matrice(int m, int n, FILE * f, int rgb);
double **citire_matrice_b(int m, int n, FILE *f, int rgb);
double **incarcare(char fisier[], int *l, int *h, int *x1, int *y1, int *x2,
				   int *y2, double **p, int *vmax, int *rgb);


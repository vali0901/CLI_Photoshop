#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/diverse.h"

double **decupare(double **mat, int *l, int *h, int *x1, int *y1, int *x2,
				  int *y2, int rgb)
{
	if (!mat) {
		printf("No image loaded\n");
	} else {
		//setarea dimensiunilor noii matrici, pentru care se aloca memorie
		int tmp_l = *x2 - *x1;
		int tmp_h = *y2 - *y1;
		double **tmp = alocare_memorie(tmp_l, tmp_h, rgb);

		for (int i = 0; i < tmp_h; i++)
			for (int j = 0; j < rgb * tmp_l; j++)
				tmp[i][j] = mat[i + (*y1)][j + rgb * (*x1)];

		mat = elim_memorie(*h, mat);
		mat = tmp;

		//actualizarea dimensiunilor noii matrici decupate
		*l = tmp_l;
		*h = tmp_h;

		//si "selectarea totala" a acesteia
		*x1 = *y1 = 0;
		*x2 = *l;
		*y2 = *h;

		printf("Image cropped\n");
	}

	return mat;
}

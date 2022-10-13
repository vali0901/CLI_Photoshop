#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "diverse.h"

double **aplicare_edge(int l, int h, int x1, int y1, int x2, int y2,
					   double **mat, int rgb, int vmax);

double **aplicare_sharpen(int l, int h, int x1, int y1, int x2, int y2,
						  double **mat, int rgb, int vmax);

double **aplicare_gaussian_blur(int l, int h, int x1, int y1, int x2, int y2,
								double **mat, int rgb, int vmax);

double **aplicare_efect(int l, int h, int x1, int y1, int x2, int y2,
						double **p, int rgb, int vmax);

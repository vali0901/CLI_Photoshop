#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double clamp(double s, int vmin, int  vmax);
void interschimbare(int *x, int *y);
void citire_rand(void);
void elim_com(FILE *f);
double **alocare_memorie(int m, int n, int rgb);
double **elim_memorie(int n, double **mat);

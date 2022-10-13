#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/diverse.h"

//functie ce verifica veridicitatea parametrului "a" al comandei SELECT
int select_param_ok(char sir[], int *a)
{
	//presupunem ca parametrul este corect
	int sw = 1;
	for (int i = 0; i < strlen(sir); i++)
		//daca parametrul nu este format exclusiv din cifre sau semnul minus
		//atunci el nu este corect
		if ((sir[i] < '0' || sir[i] > '9') && sir[i] != '-') {
			sw = 0;
			break;
		}
	if (sw == 1)
		*a = atoi(sir);
	else
		citire_rand();
	return sw;
}

//functie pentru verificarea tuturor parametrilor pentru comanda SELECT
int verif_parametrii(char sir[], int *a, int *b, int *c, int *d)
{
	//se verifica pe rand fiecare parametru, iar daca se gaseste dupa vreunul
	//din primii trei parametrii terminatorul de linie, se iese din functie,
	//insemnand ca nu au fost introdusi suficienti parametrii
	int ok = 0;
	char next_char;

	int sw_a = select_param_ok(sir, a);
	if (sw_a != 0)
		scanf("%c", &next_char);
	else
		return 0;

	if (next_char != '\n')
		scanf("%s", sir);
	else
		return 0;

	int sw_b = select_param_ok(sir, b);
	if (sw_b != 0)
		scanf("%c", &next_char);
	else
		return 0;

	if (next_char != '\n')
		scanf("%s", sir);
	else
		return 0;

	int sw_c = select_param_ok(sir, c);
	if (sw_c != 0)
		scanf("%c", &next_char);
	else
		return 0;

	if (next_char != '\n')
		scanf("%s", sir);
	else
		return 0;

	int sw_d = select_param_ok(sir, d);
	if (sw_d != 0)
		ok = 1;
	return ok;
}

void selectare(int *x1, int *y1, int *x2, int *y2, int l, int h,
			   double **mat)
{
	char sir[10];
	scanf("%s", sir);
	if (strcmp(sir, "ALL") == 0) {
		if (mat) {
			*x1 = *y1 = 0;
			*x2 = l;
			*y2 = h;
				printf("Selected ALL\n");
			} else {
				printf("No image loaded\n");
			}
	} else {
		//vom salva valorile coordonatelor in a, b, c, d temporar pentru a
		//verifica daca acestea sunt corecte, adica daca sunt in intervalul
		//[0,h] respectiv [0,l], sau daca acestea sunt diferite, in cazul in
		//care se afla pe aceeasi axa
		int a, b, c, d;
		int ok = verif_parametrii(sir, &a, &b, &c, &d);
		if (ok == 0) {
			printf("Invalid command\n");
		} else if (mat) {
			if ((a > l || b > h || c > l || d > h) || (a == c || b == d) ||
				(a < 0 || b < 0 || c < 0 || d < 0)) {
				printf("Invalid set of coordinates\n");
			} else {
				*x1 = a;
				*y1 = b;
				*x2 = c;
				*y2 = d;
				if (a > c) {
					*x1 = c;
					*x2 = a;
				}
				if (b > d) {
					*y1 = d;
					*y2 = b;
				}
				printf("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
			}
		} else {
			printf("No image loaded\n");
		}
	}
}

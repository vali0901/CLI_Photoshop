#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./include/diverse.h"
#include "./include/aplicare.h"
#include "./include/incarcare.h"
#include "./include/selectare.h"
#include "./include/rotire.h"
#include "./include/decupare.h"
#include "./include/salvare.h"

int main(void)
{
	//declararea matricei pentru imagine p, si coordonatele, dimensiunile si
	//caracteristicile accesteia

	double **p = NULL;

	int x1 = 0, x2 = 0, y1 = 0, y2 = 0, l = 0, h = 0, vmax, rgb;

	while (1) {
		char comanda[10];
		scanf("%s", comanda);
		if (strcmp(comanda, "LOAD") == 0) {
			char fisier[100];
			scanf("%s", fisier);
			p = incarcare(fisier, &l, &h, &x1, &y1, &x2, &y2, p, &vmax, &rgb);
		} else if (strcmp(comanda, "SELECT") == 0) {
			selectare(&x1, &y1, &x2, &y2, l, h, p);
		} else if (strcmp(comanda, "APPLY") == 0) {
			p = aplicare_efect(l, h, x1, y1, x2, y2, p, rgb, vmax);
		} else if (strcmp(comanda, "ROTATE") == 0) {
			p = rotire(&l, &h, &x1, &y1, &x2, &y2, p, rgb);
		} else if (strcmp(comanda, "CROP") == 0) {
			p = decupare(p, &l, &h, &x1, &y1, &x2, &y2, rgb);
		} else if (strcmp(comanda, "SAVE") == 0) {
			salvare(p, l, h, vmax, rgb);
		} else if (strcmp(comanda, "EXIT") == 0) {
			if (!p) {
				printf("No image loaded\n");
				break;
			}
			if (p) {
				p = elim_memorie(h, p);
				break;
			}
		} else {
			citire_rand();
			printf("Invalid command\n");
		}
	}
	return 0;
}

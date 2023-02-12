#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

void select_all(struct img *image)
{
	// Realizam selectia default pe imagine.
	set_full_selection(image);
	printf("Selected ALL\n");
}

void select_image(struct img *image, char operation[])
{
	// Extragem din parametrii comandei variabilele de selectie.
	char *input = strtok(operation, SEPARATORS);
	input = strtok(NULL, SEPARATORS);
	int x1 = atoi(input);
	input = strtok(NULL, SEPARATORS);
	int y1 = atoi(input);
	input = strtok(NULL, SEPARATORS);
	int x2 = atoi(input);
	input = strtok(NULL, SEPARATORS);
	int y2 = atoi(input);
	// Verificam daca datele sunt valide si eventual facem swap
	// intre ele (daca ordinea nu este corecta).
	if (invalid_coordinates(x1, x2, y1, y2, image)) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (x1 > x2)
		swap_values(&x1, &x2);
	if (y1 > y2)
		swap_values(&y1, &y2);
	// Salvam in memorie selectia.
	image->x1 = x1;
	image->x2 = x2;
	image->y1 = y1;
	image->y2 = y2;
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
}

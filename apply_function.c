#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

const int KERNEL_EDGE[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}},
		  KERNEL_SHARPEN[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}},
		  KERNEL_BLUR[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
		  KERNEL_GAUSS_BLUR[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

const char FILTERS[4][15] = {"EDGE", "SHARPEN", "BLUR", "GAUSSIAN_BLUR"};

int invalid_parameter(char my_filter[])
{
	// Prin aceasta functie verificam daca parametrul
	// functie APPLY este valid.
	for (int i = 0; i < 4; ++i)
		if (strcmp(my_filter, FILTERS[i]) == 0)
			return 0;
	return 1;
}

void apply_filter(int *new_pixel, int old_pixel, char type_filter[],
				  int curr_line, int curr_column)
{
	// Aplicam filtrul ales pe un pixel.
	if (strcmp(type_filter, "EDGE") == 0)
		*new_pixel += old_pixel * KERNEL_EDGE[curr_line][curr_column];
	else if (strcmp(type_filter, "SHARPEN") == 0)
		*new_pixel += old_pixel * KERNEL_SHARPEN[curr_line][curr_column];
	else if (strcmp(type_filter, "BLUR") == 0)
		*new_pixel += old_pixel * KERNEL_BLUR[curr_line][curr_column];
	else if (strcmp(type_filter, "GAUSSIAN_BLUR") == 0)
		*new_pixel += old_pixel * KERNEL_GAUSS_BLUR[curr_line][curr_column];
}

void filter(struct img *image, char type_filter[], int *operation_failed)
{
	// Afisam mesajele de eroare daca nu exista o imagine incarcata
	// sau daca este invalida (de tip grayscale).
	if (invalid_parameter(type_filter)) {
		printf("APPLY parameter invalid\n");
		return;
	}
	if (!is_rgb(image->image_format)) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	// Facem o copie a imaginii initiale, pentru a nu pierde date.
	int ***new_image;
	alloc_entire_collection(&new_image, image->height, image->width,
							FORMAT_LEN, operation_failed);
	// Daca o alocare nu a functionat, marcam acest lucru prin variabila
	// operation_failed si iesim din program.
	if (*operation_failed)
		return;
	for (int i = 0; i < image->height; ++i)
		for (int j = 0; j < image->width; ++j)
			for (int k = 0; k < FORMAT_LEN; ++k)
				new_image[i][j][k] = image->RGB[i][j][k];
	// Parcurgem fiecare pixel din selectie si il modificam in functie de
	// filtrul introdus ca parametru.
	for (int i = image->y1; i < image->y2; ++i) {
		for (int j = image->x1; j < image->x2; ++j) {
			// Verificam daca pixelul curent nu se afla pe marginea matricei.
			if (!(i > 0 && j > 0 && i < image->height - 1 &&
				  j < image->width - 1))
				continue;
			for (int k = 0; k < FORMAT_LEN; ++k) {
				new_image[i][j][k] = 0;
				for (int line = 0; line < FORMAT_LEN; ++line)
					for (int col = 0; col < FORMAT_LEN; ++col)
						apply_filter(&new_image[i][j][k],
									 image->RGB[i + line - 1][j + col - 1][k],
									 type_filter, line, col);
				if (strcmp(type_filter, "BLUR") == 0)
					new_image[i][j][k] /= 9;
				if (strcmp(type_filter, "GAUSSIAN_BLUR") == 0)
					new_image[i][j][k] /= 16;
				new_image[i][j][k] = clamp(new_image[i][j][k], 0, 255);
			}
		}
	}
	// Copiem in memorie imaginea dupa aplicarea filtrului.
	for (int i = image->y1; i < image->y2; ++i)
		for (int j = image->x1; j < image->x2; ++j)
			for (int k = 0; k < FORMAT_LEN; ++k)
				image->RGB[i][j][k] = new_image[i][j][k];
	// Eliberam memoria pentru matricea folosita
	// ca imagine auxiliara.
	clear_RGB_image(new_image, image->height, image->width);
	printf("APPLY %s done\n", type_filter);
}

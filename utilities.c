#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BINS 256

#include "utilities.h"

void alloc_RGB(struct img *image, int *operation_failed)
{
	// In aceasta functie alocam memoria necesara pentru memorarea unei imagini
	// de tip rgb intr - o matrice, iar daca ceva nu a fost alocat
	// corect, marcam acest fapt prin variabila operation_failed si dealocam
	// din memorie tot ce am folosit pana la acel moment.
	image->RGB = (int ***)malloc(image->height * sizeof(int **));
	if (!image->RGB) {
		*operation_failed = 1;
		return;
	}
	for (int i = 0; i < image->height; ++i) {
		image->RGB[i] = (int **)malloc(image->width * sizeof(int *));
		if (*operation_failed) {
			for (int j = 0; j < i; ++j)
				free(image->RGB[j]);
			free(image->RGB);
			return;
		}
		for (int j = 0; j < image->width; ++j)
			image->RGB[i][j] = (int *)malloc(FORMAT_LEN * sizeof(int));
	}
}

void alloc_NRGB(struct img *image, int *operation_failed)
{
	// In aceasta functie alocam memoria necesara pentru memorarea unei imagini
	// de tip grayscalea intr - o matrice, iar daca ceva nu a fost alocat
	// corect, marcam acest fapt prin variabila operation_failed si dealocam
	// din memorie tot ce am folosit pana la acel moment.
	image->NRGB = (int **)malloc(image->height * sizeof(int *));
	if (!image->NRGB) {
		printf("Invalid allocation.\n");
		*operation_failed = 1;
		free(image->NRGB);
		return;
	}
	for (int i = 0; i < image->height; ++i) {
		image->NRGB[i] = (int *)malloc(image->width * sizeof(int));
		if (!image->NRGB[i]) {
			// Dealocam toata memoria folosita pana acum
			for (int j = 0; j < i; ++j)
				free(image->NRGB[j]);
			printf("Invalid allocation.\n");
			*operation_failed = 1;
			return;
		}
	}
}

void clear_RGB_image(int ***map_pixels, int height, int width)
{
	// In aceasta functie eliberam memoria folosita dintr - o colectie de
	// matrice in care memoram o imagine de tip RGB.
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j)
			free(map_pixels[i][j]);
		free(map_pixels[i]);
	}
	free(map_pixels);
}

void clear_NRGB_image(int **map_pixels, int height)
{
	// In aceasta functie eliberam memoria folosita dintr - o
	// matrice in care memoram o imagine de tip NRGB.
	for (int i = 0; i < height; ++i)
		free(map_pixels[i]);
	free(map_pixels);
}

void alloc_collection(int ****collection, int size, int *opperation_failed)
{
	// Prin aceasta functie alocam memorie pentru o colectie de matrice.
	// Daca alocarea nu a fost facuta corect returnam prin variabila
	// opperation_failed valoarea 1.
	(*collection) = (int ***)malloc(size * sizeof(int **));
	if (!(*collection)) {
		printf("Invalid allocation.\n");
		*opperation_failed = 1;
		return;
	}
}

void alloc_matrix(int ***matrix, int lines, int columns, int *operation_failed)
{
	// In aceasta functie alocam memoria necesara pentru o matrice si daca
	// ceva nu a fost alocat cum trebuie marcam acest fapt prin variabila
	// operation_failed si dealocam din memorie tot ce am folosit pana la
	// acel moment.
	(*matrix) = (int **)malloc(lines * sizeof(int *));
	if (!(*matrix)) {
		printf("Invalid allocation.\n");
		*operation_failed = 1;
		return;
	}
	for (int i = 0; i < lines; ++i) {
		(*matrix)[i] = (int *)malloc(columns * sizeof(int));
		if (!(*matrix)[i]) {
			// Dealocam toata memoria folosita pana acum
			for (int j = 0; j < i; ++j)
				free((*matrix)[j]);
			printf("Invalid allocation.\n");
			*operation_failed = 1;
			return;
		}
	}
}

void free_matrix(int **matrix, int size)
{
	// In aceasta functie eliberam memoria alocata pentru o matrice.
	for (int i = 0; i < size; ++i)
		free(matrix[i]);
	free(matrix);
}

void alloc_entire_collection(int ****collection, int size_1, int size_2,
							 int size_3, int *operation_failed)
{
	// Prin aceasta functie alocam memoria necesara pentru o colectie de
	// matrice impreuna cu memoria pentru fiecare matrice in parte.
	// Daca ceva nu a mers, pur si simplu dealocam memoria folosita
	// pana la acel moment si marcam variabila opperation_failed.
	alloc_collection(collection, size_1, operation_failed);
	if (*operation_failed)
		return;
	for (int i = 0; i < size_1; ++i) {
		alloc_matrix(&((*collection)[i]), size_2, size_3,
					 operation_failed);
		if (*operation_failed) {
			for (int j = 0; j < i; ++j)
				free_matrix((*collection)[j], size_2);
			free(*collection);
			return;
		}
	}
}

void swap_values(int *value_1, int *value_2)
{
	// In aceasta functie facem swap intre doua valori folosind pointeri.
	int aux = *value_1;
	*value_1 = *value_2;
	*value_2 = aux;
}

int valid_angle(int angle)
{
	// In aceasta functie verificam daca unghiul de rotatie a unei
	// matrice este unul valid (multiplu de 90 de grade).
	const int valid_angles[] = {0, -90, 90, -180, 180, -270, 270, -360, 360};
	for (int i = 0; i < 9; ++i)
		if (angle == valid_angles[i])
			return 1;
	return 0;
}

int is_rgb(char image_type[])
{
	// In aceasta functie verificam daca tipul imaginii din memorie este RGB.
	return (strcmp(image_type, "P3") == 0 || strcmp(image_type, "P6") == 0);
}

void set_full_selection(struct img *image)
{
	// In aceasta functie setam valorile default
	// pentru variabilele de selectie.
	image->x1 = 0;
	image->x2 = image->width;
	image->y1 = 0;
	image->y2 = image->height;
}

int is_selected(struct img image)
{
	// In aceasta functie verificam daca exista o selectie
	// diferita de cea default.
	return (!(image.x1 == 0 && image.y1 == 0 && image.x2 == image.width &&
			  image.y2 == image.height));
}

int max(int value_1, int value_2)
{
	// Aceasta functie returneaza maximul dintre 2 valori.
	if (value_1 > value_2)
		return value_1;
	return value_2;
}

void clear_image(struct img *image)
{
	// In aceasta functie eliberam memoria folosita pentru
	// retinerea unei imagini in memorie.
	if (image->in_editor == 0) {
		printf("No image loaded\n");
		return;
	}
	if (is_rgb(image->image_format))
		clear_RGB_image(image->RGB, image->height, image->width);
	else
		clear_NRGB_image(image->NRGB, image->height);
}

int invalid_coordinates(int x1, int x2, int y1, int y2, struct img *image)
{
	// Prin aceasta functie verificam daca valorile variabilelor de selectie
	// date de utilizator sunt valide.
	return (x1 < 0 || x1 >= image->width || x2 < 0 || x2 > image->width ||
			y1 < 0 || y1 >= image->height || y2 < 0 || y2 > image->height ||
			x1 == x2 || y1 == y2);
}

int *get_frequence(struct img *image, int *operation_failed)
{
	// Prin aceasta functie returnam vectorul de frecventa a
	// valorilor pixelilor folositi in intreaga imagine (de tip grayscale).
	int *freq = (int *)calloc(MAX_BINS, sizeof(int));
	// Daca alocarea nu a functionat, marcam acest fapt prin variabila
	// operation_failed si iesim din program.
	if (!freq) {
		*operation_failed = 1;
		return NULL;
	}
	for (int i = 0; i < image->height; ++i)
		for (int j = 0; j < image->width; ++j)
			freq[image->NRGB[i][j]]++;
	return freq;
}

int clamp(int x, int minimum, int maximum)
{
	if (x < minimum)
		x = minimum;
	else if (x > maximum)
		x = maximum;
	return x;
}

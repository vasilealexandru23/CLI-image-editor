#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utilities.h"
#define RIGHT_ANGLE 90

void rotate_selection(struct img *image, int angle, int *operation_failed)
{
	// Verificam daca unghiul de rotatie este valid.
	if (!valid_angle(angle)) {
		printf("Unsupported rotation angle\n");
		return;
	}
	if (image->x2 - image->x1 != image->y2 - image->y1) {
		printf("The selection must be square\n");
		return;
	}
	int sub_matrix_size = image->y2 - image->y1;
	if (is_rgb(image->image_format)) {
		for (int quadrant = 0; quadrant < abs(angle) / RIGHT_ANGLE;
			 ++quadrant) {
			// Creez o matrice auxiliara in care calculez matricea rotita.
			int ***aux;
			alloc_entire_collection(&aux, sub_matrix_size, sub_matrix_size,
									FORMAT_LEN, operation_failed);
			// Daca alocarea nu a functionat iesim din program.
			if (*operation_failed)
				return;
			// Calculez fiecare element din matricea rotita, fie in sens
			// trigonometric, fie in sens invers-trigonometric cu
			// formulele aferente.
			for (int i = 0; i < sub_matrix_size; ++i)
				for (int j = 0; j < sub_matrix_size; ++j)
					for (int k = 0; k < FORMAT_LEN; ++k)
						aux[i][j][k] = (angle > 0 ? image->RGB
						[image->y2 - j - 1][image->x1 + i][k] :
						image->RGB[image->y1 + j][image->x2 - i - 1][k]);
			// Actualizez imaginea cu selectia rotita.
			for (int i = image->y1; i < image->y2; ++i)
				for (int j = image->x1; j < image->x2; ++j)
					for (int k = 0; k < FORMAT_LEN; ++k)
						image->RGB[i][j][k] =
							aux[i - image->y1][j - image->x1][k];
			// Eliberam matricea auxiliara folosita.
			clear_RGB_image(aux, sub_matrix_size, sub_matrix_size);
		}
	} else {
		for (int c = 0; c < abs(angle) / 90; ++c) {
			// Creez o matrice auxiliara in care calculez matricea rotita.
			int **aux;
			alloc_matrix(&aux, sub_matrix_size, sub_matrix_size,
						 operation_failed);
			// Daca alocarea nu a functionat iesim din program.
			if (*operation_failed)
				return;
			// Calculez fiecare element din matricea rotita, fie in sens
			// trigonometric, fie in sens invers-trigonometric cu
			// formulele aferente.
			for (int i = 0; i < sub_matrix_size; ++i)
				for (int j = 0; j < sub_matrix_size; ++j)
					if (angle > 0)
						aux[i][j] =
							image->NRGB[image->y2 - j - 1][image->x1 + i];
					else
						aux[i][j] =
							image->NRGB[image->y1 + j][image->x2 - i - 1];
			for (int i = image->y1; i < image->y2; ++i)
				for (int j = image->x1; j < image->x2; ++j)
					image->NRGB[i][j] = aux[i - image->y1][j - image->x1];
			// Eliberam matricea auxiliara folosita.
			clear_NRGB_image(aux, sub_matrix_size);
		}
	}
	printf("Rotated %d\n", angle);
}

void rotate_image(struct img *image, int angle, int *operation_failed)
{
	// Verificam daca unghiul de rotatie este valid.
	if (!valid_angle(angle)) {
		printf("Unsupported rotation angle\n");
		return;
	}
	if (is_rgb(image->image_format)) {
		for (int quadrant = 0; quadrant < abs(angle) / RIGHT_ANGLE;
			 ++quadrant) {
			// Creez o matrice auxiliara in care calculez imaginea rotita.
			int ***aux;
			alloc_entire_collection(&aux, image->width, image->height,
									FORMAT_LEN, operation_failed);
			// Daca alocarea nu a functionat iesim din program.
			if (*operation_failed)
				return;
			// Calculez fiecare element din imaginea rotita, fie in sens
			// trigonometric, fie in sens invers-trigonometric cu
			// formulele aferente.
			for (int i = 0; i < image->width; ++i)
				for (int j = 0; j < image->height; ++j)
					for (int k = 0; k < 3; ++k)
						aux[i][j][k] = (angle > 0 ? image->RGB
						[image->height - j - 1][i][k] : image->RGB
						[j][image->width - i - 1][k]);
			// Eliberam memoria folosita pentru imaginea initiala, actualizam
			// caracteristicile imagnii si facem o noua alocare de memorie.
			clear_RGB_image(image->RGB, image->height, image->width);
			swap_values(&image->height, &image->width);
			alloc_RGB(image, operation_failed);
			// Daca alocarea nu a functionat eliberam memoria
			// folosita pana acum si iesim din program.
			if (*operation_failed) {
				clear_RGB_image(aux, image->height, image->width);
				return;
			}
			// Salvam imaginea rotita si eliberam matricea auxiliara folosita.
			for (int i = 0; i < image->height; ++i)
				for (int j = 0; j < image->width; ++j)
					for (int k = 0; k < 3; ++k)
						image->RGB[i][j][k] = aux[i][j][k];
			clear_RGB_image(aux, image->height, image->width);
		}
	} else {
		for (int quadrant = 0; quadrant < abs(angle) / RIGHT_ANGLE;
			 ++quadrant) {
			// Creez o matrice auxiliara in care calculez imaginea rotita.
			int **aux;
			alloc_matrix(&aux, image->width, image->height, operation_failed);
			// Daca alocarea nu a functionat iesim din program.
			if (*operation_failed)
				return;
			// Calculez fiecare element din imaginea rotita, fie in sens
			// trigonometric, fie in sens invers-trigonometric cu
			// formulele aferente.
			for (int i = 0; i < image->width; ++i)
				for (int j = 0; j < image->height; ++j)
					aux[i][j] = (angle > 0 ?
								 image->NRGB[image->height - j - 1][i] :
								 image->NRGB[j][image->width - i - 1]);
			// Eliberam memoria folosita pentru imaginea initiala, actualizam
			// caracteristicile imagnii si facem o noua alocare de memorie.
			clear_NRGB_image(image->NRGB, image->height);
			swap_values(&image->height, &image->width);
			alloc_NRGB(image, operation_failed);
			// Daca alocarea nu a functionat eliberam memoria
			// folosita pana acum si iesim din program.
			if (*operation_failed) {
				clear_NRGB_image(aux, image->width);
				return;
			}
			// Salvam imaginea rotita si eliberam matricea auxiliara folosita.
			for (int i = 0; i < image->height; ++i)
				for (int j = 0; j < image->width; ++j)
					image->NRGB[i][j] = aux[i][j];
			clear_NRGB_image(aux, image->height);
		}
	}
	printf("Rotated %d\n", angle);
	set_full_selection(image);
}

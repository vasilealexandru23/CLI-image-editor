#include <stdio.h>
#include "utilities.h"

void crop_image(struct img *image, int *operation_failed)
{
	int nr_lines = image->y2 - image->y1;
	int nr_columns = image->x2 - image->x1;
	if (is_rgb(image->image_format)) {
		// Alocam o matrice auxiliara in care salvam elementele imaginii
		// din memorie.
		int ***aux;
		alloc_entire_collection(&aux, nr_lines, nr_columns, FORMAT_LEN,
								operation_failed);
		// Daca alocarea nu a functionat, iesim din program.
		if (*operation_failed)
			return;
		// Copiem in matricea auxiliara elementele din sectiunea dorita.
		for (int i = image->y1; i < image->y2; ++i)
			for (int j = image->x1; j < image->x2; ++j)
				for (int k = 0; k < FORMAT_LEN; ++k)
					aux[i - image->y1][j - image->x1][k] = image->RGB[i][j][k];
		// Actualizam noile dimensiuni ale imaginii.
		clear_RGB_image(image->RGB, image->height, image->width);
		image->height = nr_lines;
		image->width = nr_columns;
		alloc_RGB(image, operation_failed);
		// Daca alocarea nu a functionat, eliberam tot ceea ce am folosit
		// pana acum si iesim din program.
		if (*operation_failed) {
			clear_RGB_image(aux, nr_lines, nr_columns);
			return;
		}
		// Actualizam imaginea din memorie si eliberam memoria folosita
		// in mod auxiliar pana acum.
		for (int i = 0; i < nr_lines; ++i)
			for (int j = 0; j < nr_columns; ++j)
				for (int k = 0; k < FORMAT_LEN; ++k)
					image->RGB[i][j][k] = aux[i][j][k];
		clear_RGB_image(aux, nr_lines, nr_columns);
	} else {
		int **aux;
		// Alocam o matrice auxiliara in care salvam elementele imaginii
		// din memorie.
		alloc_matrix(&aux, nr_lines, nr_columns, operation_failed);
		// Daca alocarea nu a functionat, iesim din program.
		if (*operation_failed)
			return;
		// Copiem in matricea auxiliara elementele din sectiunea dorita.
		for (int i = image->y1; i < image->y2; ++i)
			for (int j = image->x1; j < image->x2; ++j)
				aux[i - image->y1][j - image->x1] = image->NRGB[i][j];
		// Actualizam noile dimensiuni ale imaginii.
		clear_NRGB_image(image->NRGB, image->height);
		image->height = nr_lines;
		image->width = nr_columns;
		alloc_NRGB(image, operation_failed);
		// Daca alocarea nu a functionat, eliberam tot ceea ce am folosit
		// pana acum si iesim din program.
		if (*operation_failed) {
			clear_NRGB_image(aux, nr_lines);
			return;
		}
		// Actualizam imaginea din memorie si eliberam memoria folosita
		// in mod auxiliar pana acum.
		for (int i = 0; i < nr_lines; ++i)
			for (int j = 0; j < nr_columns; ++j)
				image->NRGB[i][j] = aux[i][j];
		clear_NRGB_image(aux, nr_lines);
	}
	printf("Image cropped\n");
	// Setam selectia default.
	set_full_selection(image);
}

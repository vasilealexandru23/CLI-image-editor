#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utilities.h"

void equalize(struct img *image, int *operation_failed)
{
	// Afisam mesajul de eroare daca imaginea este
	// invalida (de tip RGB).
	if (is_rgb(image->image_format)) {
		printf("Black and white image needed\n");
		return;
	}
	// Aflam vectorul de frecventa pentru valorile pixelilor din imagine.
	int *freq = get_frequence(image, operation_failed);
	// Daca alocarea nu a functionat, iesim din program.
	if (*operation_failed)
		return;
	// Parcurgem fiecare pixel din imagine si aplicam formula
	// corespunzatoare fiecaruia in parte.
	for (int i = 0; i < image->height; ++i) {
		for (int j = 0; j < image->width; ++j) {
			double new_pixel = 1.0 * 255 / (image->height * image->width);
			int sum = 0;
			for (int curr_pixel = 0;
					curr_pixel <= image->NRGB[i][j]; ++curr_pixel)
				sum += freq[curr_pixel];
			image->NRGB[i][j] = clamp(round(new_pixel * (1.0 * sum)), 0, 255);
		}
	}
	printf("Equalize done\n");
	// Eliberam memoria folosita pana acum in program.
	free(freq);
}

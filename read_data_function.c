#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#define MAX_LINE_LENGTH (int)(1e6 + 5)

void remove_comments(FILE *pointer_original_file)
{
	FILE *pointer_aux_file = fopen("aux_file", "w");
	char line[MAX_LINE_LENGTH];
	while (fgets(line, MAX_LINE_LENGTH, pointer_original_file)) {
		if (line[0] == '#')
			continue;
		fprintf(pointer_aux_file, "%s", line);
	}
	fclose(pointer_aux_file);
	pointer_aux_file = fopen("aux_file", "r");
	while (fgets(line, MAX_LINE_LENGTH, pointer_aux_file))
		fprintf(pointer_original_file, "%s", line);
}

void load_image(struct img *image, char file_name[], int *operation_failed)
{
	FILE *fin;
	fin = fopen(file_name, "r");
	// Eliberam, daca avem o imagine in editor, memoria folosita
	// pentru salvarea ei in memorie.
	if (image->in_editor == 1) {
		clear_image(image);
		image->in_editor = 0;
	}
	if (!fin) {
		printf("Failed to load %s\n", file_name);
		return;
	}
	// remove_comments(fin);
	image->in_editor = 1;
	// Citim informatiile despre noua imagine si le salvam
	// in variabilele corespunzatoare.
	fgets(image->image_format, FORMAT_LEN, fin);
	image->image_format[(int)strlen(image->image_format)] = '\0';
	fscanf(fin, "%d%d%d ", &image->width, &image->height,
		   &(*image).max_col_val);
	if (is_rgb(image->image_format)) {
		// Alocam memoria pentru noua imagine de tip RGB, iar daca
		// ceva nu a functionat la alocare iesim din program.
		alloc_RGB(image, operation_failed);
		if (*operation_failed)
			return;
		for (int i = 0; i < image->height; ++i) {
			for (int j = 0; j < image->width; ++j) {
				for (int k = 0; k < FORMAT_LEN; ++k) {
					// Avem doua cazuri de citire pentru format text si binar.
					if (strcmp(image->image_format, "P3") == 0) {
						fscanf(fin, "%d", &image->RGB[i][j][k]);
					} else {
						unsigned char aux;
						fread(&aux, sizeof(unsigned char), 1, fin);
						image->RGB[i][j][k] = (int)(aux);
					}
				}
			}
		}
	} else {
		// Alocam memoria pentru noua imagine de tip grayscale, iar daca
		// ceva nu a functionat la alocare iesim din program.
		alloc_NRGB(image, operation_failed);
		if (*operation_failed)
			return;
		for (int i = 0; i < image->height; ++i) {
			for (int j = 0; j < image->width; ++j) {
				// Avem doua cazuri de citire pentru format text si binar.
				if (strcmp(image->image_format, "P2") == 0) {
					fscanf(fin, "%d", &image->NRGB[i][j]);
				} else {
					unsigned char aux;
					fread(&aux, sizeof(char), 1, fin);
					image->NRGB[i][j] = (int)aux;
				}
			}
		}
	}
	// Setam selectia default.
	set_full_selection(image);
	fclose(fin);
	printf("Loaded %s\n", file_name);
}

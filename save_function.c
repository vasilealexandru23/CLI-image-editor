#include <stdio.h>
#include "utilities.h"

void save_image(struct img image, char output_file[], int binary_format)
{
	// Deschidem fisierul in care vream sa salvam imaginea.
	FILE *fout = fopen(output_file, "w");
	if (!fout) {
		printf("Failed to load %s\n", output_file);
		return;
	}
	if (is_rgb(image.image_format)) {
		// Cazul cand salvam o imagine de tip RGB.
		if (!binary_format)
			fprintf(fout, "P3\n");
		else
			fprintf(fout, "P6\n");
		fprintf(fout, "%d %d\n%d\n", image.width, image.height,
				image.max_col_val);
		for (int i = 0; i < image.height; ++i) {
			for (int j = 0; j < image.width; ++j) {
				for (int k = 0; k < FORMAT_LEN; ++k) {
					if (!binary_format) {
						fprintf(fout, "%d ", image.RGB[i][j][k]);
					} else {
						// Alegem o variabila auxiliara prin care sa facem
						// o compresie a valorilor pixelilor (conversie int
						// la cod ascii).
						unsigned char aux = (unsigned char)image.RGB[i][j][k];
						fwrite(&aux, sizeof(unsigned char), 1, fout);
					}
				}
			}
			if (!binary_format)
				fprintf(fout, "\n");
		}
	} else {
		// Cazul cand salvam o imagine de tip grayscale.
		if (!binary_format)
			fprintf(fout, "P2\n");
		else
			fprintf(fout, "P5\n");
		fprintf(fout, "%d %d\n%d\n", image.width, image.height,
				image.max_col_val);
		for (int i = 0; i < image.height; ++i) {
			for (int j = 0; j < image.width; ++j) {
				if (!binary_format) {
					fprintf(fout, "%d ", image.NRGB[i][j]);
				} else {
					// Alegem o variabila auxiliara prin care sa facem
					// o compresie a valorilor pixelilor (conversie int
					// la cod ascii).
					unsigned char aux = (unsigned char)image.NRGB[i][j];
					fwrite(&aux, sizeof(unsigned char), 1, fout);
				}
			}
			if (!binary_format)
				fprintf(fout, "\n");
		}
	}
	printf("Saved %s\n", output_file);
	fclose(fout);
}

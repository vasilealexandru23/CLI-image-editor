#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#define MAX_BINS 256

void histogram(struct img image, const int nr_stars, const int nr_bins,
			   int *operation_failed)
{
	// Afisam mesajele de eroare daca nu exista o imagine incarcata
	// sau daca este invalida (de tip RGB).
	if (is_rgb(image.image_format)) {
		printf("Black and white image needed\n");
		return;
	}
	// Aflam lungimea unui interval pentru histograma si frecventa
	// valorilor fiecarui piexel in parte.
	int interval_len = MAX_BINS / nr_bins;
	int *freq = get_frequence(&image, operation_failed);
	// Verificam daca alocarea a fost corect realizata.
	if (*operation_failed)
		return;
	int max_freq = 0;
	// Stabilim elementele necesare formulei aferente si o aplicam.
	for (int curr_bin = 0; curr_bin < nr_bins; ++curr_bin) {
		int sum_freq = 0;
		// Parcurgem fiecare valoare din binul curent.
		for (int values_bin = curr_bin * interval_len; values_bin <
			 (curr_bin + 1) * interval_len; ++values_bin)
			sum_freq += freq[values_bin];
		max_freq = max(max_freq, sum_freq);
	}
	for (int curr_bin = 0; curr_bin < nr_bins; ++curr_bin) {
		int sum_freq = 0;
		// Parcurgem fiecare valoare din binul curent.
		for (int values_bin = curr_bin * interval_len; values_bin <
			 (curr_bin + 1) * interval_len; ++values_bin)
			sum_freq += freq[values_bin];
		// Aplicam formula aferenta si afisam.
		int histogram_value = (int)(1.0 * sum_freq / max_freq * nr_stars);
		printf("%d\t|\t", histogram_value);
		while (histogram_value--)
			printf("*");
		printf("\n");
	}
	// Eliberam memoria folosita pentru vectorul de frecventa.
	free(freq);
}

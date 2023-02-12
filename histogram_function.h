#ifndef __HISTOGRAM_FUNCTION_H__
#define __HISTOGRAM_FUNCTION_H__

#include "utilities.h"

int *get_frequence(struct img *image, int *operation_failed);

void histogram(struct img image, const int nr_stars, const int nr_bins,
			   int *operation_failed);

#endif // __HISTOGRAM_FUNCTION_H__

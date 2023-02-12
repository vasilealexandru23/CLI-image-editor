#ifndef __APPLY_FUNCTION_H__
#define __APPLY_FUNCTION_H__

#include "utilities.h"

int invalid_parameter(char my_filter[]);

void apply_filter(int *new_pixel, int old_pixel, char type_filter[],
				  int curr_line, int curr_column);

void filter(struct img *image, char type_filter[], int *operation_failed);

#endif // __APPLY_FUNCTION_H__

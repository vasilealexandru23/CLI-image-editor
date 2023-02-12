#ifndef __READ_DATA_FUNCTION_H__
#define __READ_DATA_FUNCTION_H__

#include "utilities.h"
#include <stdio.h>

void remove_comments(FILE * pointer_original_file);
void load_image(struct img *image, char file_name[], int *operation_failed);

#endif // __READ_DATA_FUNCTION_H__

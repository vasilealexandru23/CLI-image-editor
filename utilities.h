#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#define FORMAT_LEN 3
#define SEPARATORS "\n "
#define OPERATION_LEN 100

struct img {
	char image_format[FORMAT_LEN];
	int height, width, max_col_val, in_editor;
	int ***RGB, **NRGB;
	// for selection command
	int x1, x2, y1, y2;
};

void alloc_RGB(struct img *image, int *operation_failed);

void alloc_NRGB(struct img *image, int *operation_failed);

void clear_RGB_image(int ***map_pixels, int height, int width);

void clear_NRGB_image(int **map_pixels, int height);

void alloc_collection(int ****collection, int size, int *opperation_failed);

void alloc_matrix(int ***matrix, int lines, int columns, int *operation_failed);

void free_matrix(int **matrix, int size);

void alloc_entire_collection(int ****collection, int size_1, int size_2,
							 int size_3, int *operation_failed);

void swap_values(int *value_1, int *value_2);

int valid_angle(int angle);

int is_rgb(char image_type[]);

void set_full_selection(struct img *image);

int is_selected(struct img image);

int max(int value_1, int value_2);

void clear_image(struct img *image);

int invalid_coordinates(int x1, int x2, int y1, int y2, struct img *image);

int *get_frequence(struct img *image, int *operation_failed);

int clamp(int x, int minimum, int maximum);

#endif // __UTILITIES_H__

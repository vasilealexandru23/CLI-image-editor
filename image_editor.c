#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "apply_function.h"
#include "correct_commands.h"
#include "crop_function.h"
#include "equalize_function.h"
#include "histogram_function.h"
#include "read_data_function.h"
#include "rotate_function.h"
#include "save_function.h"
#include "select_function.h"
#include "utilities.h"

#define NR_COMMANDS 7
#define LENGTH_COMMAND 10

const char commands[NR_COMMANDS][LENGTH_COMMAND] = {
	"APPLY", "HISTOGRAM", "ROTATE", "SELECT", "EQUALIZE", "SAVE", "CROP"};

int valid_commands(char command[])
{
	for (int i = 0; i < 7; ++i)
		if (strcmp(commands[i], command) == 0)
			return 1;
	return 0;
}

int main(void)
{
	char operation[OPERATION_LEN];
	struct img image;
	image.in_editor = 0;
	int operation_failed = 0;
	while (1) {
		// Verificam daca vreo alocare nu a functionat si daca da,
		// eliberam toata memoria folosita in program.
		if (operation_failed) {
			clear_image(&image);
			exit(0);
		}
		fgets(operation, OPERATION_LEN, stdin);
		char copy_operation[OPERATION_LEN];
		strcpy(copy_operation, operation);
		copy_operation[(int)strlen(operation)] = '\0';
		char *input = strtok(operation, SEPARATORS);
		if (image.in_editor == 0 && valid_commands(input)) {
			printf("No image loaded\n");
			continue;
		}
		// Verificam daca comanda data de utilizator este valida,
		// extragem parametrii si apelam functiile corespunzatoare.
		if (check_load_command(copy_operation)) {
			input = strtok(copy_operation, " ");
			input = strtok(NULL, SEPARATORS);
			load_image(&image, input, &operation_failed);
		} else if (check_select_command(copy_operation)) {
			select_image(&image, copy_operation);
		} else if (check_select_all_command(copy_operation)) {
			select_all(&image);
		} else if (check_crop_command(copy_operation)) {
			crop_image(&image, &operation_failed);
		} else if (check_save_command(copy_operation)) {
			input = strtok(copy_operation, " ");
			input = strtok(NULL, SEPARATORS);
			char output_file[OPERATION_LEN];
			strcpy(output_file, input);
			output_file[strlen(output_file)] = '\0';
			input = strtok(NULL, SEPARATORS);
			if (!input)
				save_image(image, output_file, 1);
			else
				save_image(image, output_file, 0);
		} else if (check_rotate_command(copy_operation)) {
			input = strtok(copy_operation, SEPARATORS);
			input = strtok(NULL, SEPARATORS);
			int angle = atoi(input);
			if (is_selected(image))
				rotate_selection(&image, angle, &operation_failed);
			else
				rotate_image(&image, angle, &operation_failed);
		} else if (check_apply_command(copy_operation)) {
			input = strtok(copy_operation, " ");
			input = strtok(NULL, SEPARATORS);
			filter(&image, input, &operation_failed);
		} else if (check_histogram_command(copy_operation)) {
			input = strtok(copy_operation, " ");
			input = strtok(NULL, SEPARATORS);
			const int X = atoi(input);
			input = strtok(NULL, SEPARATORS);
			const int Y = atoi(input);
			histogram(image, X, Y, &operation_failed);
		} else if (check_equalize_command(copy_operation)) {
			equalize(&image, &operation_failed);
		} else if (check_exit_command(copy_operation)) {
			clear_image(&image);
			exit(0);
		} else {
			printf("Invalid command\n");
		}
	}
	return 0;
}

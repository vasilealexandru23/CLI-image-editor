#include <stdio.h>
#include <string.h>
#define SEPARATORS "\n "
#define OPERATION_LEN 100

int check_number(char input[])
{
	// In aceasta functie verificam daca un sir de caracter
	// este un numar(pozitiv sau negativ);
	if (!input)
		return 0;
	if (!(input[0] == '-' || (input[0] >= '0' && input[0] <= '9')))
		return 0;
	for (int i = 1; i < (int)strlen(input); ++i)
		if (!(input[i] >= '0' && input[i] <= '9'))
			return 0;
	return 1;
}

int check_select_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei select
	// introdus de utilizator este valid, adica formatul sa fie :
	// SELECT NUMAR NUMAR NUMAR NUMAR NULL (NULL este de la strtok
	// prin care verificam daca nu mai este un parametru sau, eventual,
	// mai multi, in comanda data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (strcmp(input, "SELECT") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!check_number(input))
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!check_number(input))
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!check_number(input))
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!check_number(input))
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (input)
		return 0;
	return 1;
}

int check_select_all_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei select all
	// introdus de utilizator este valid, adica formatul sa fie :
	// SELECT ALL NULL (NULL este de la strtok prin care verificam daca
	// nu mai este un parametru sau eventual, mai multi, in comanda
	// data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (!input || strcmp(input, "SELECT") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!input || strcmp(input, "ALL") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (input)
		return 0;
	return 1;
}

int check_histogram_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei histogram
	// introdus de utilizator este valid, adica formatul sa fie :
	// HISTOGRAM NUMAR NUMAR NULL (NULL este de la strtok
	// prin care verificam daca nu mai este un parametru sau, eventual,
	// mai multi, in comanda data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (strcmp(input, "HISTOGRAM") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!check_number(input))
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!check_number(input))
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (input)
		return 0;
	return 1;
}

int check_save_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei save
	// introdus de utilizator este valid, adica formatul sa fie :
	// SAVE NUME NULL/ascii NULL (NULL este de la strtok prin care
	// verificam daca nu mai este un parametru sau, eventual,
	// mai multi, in comanda data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (strcmp(input, "SAVE") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!input)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!input)
		return 1;
	if (strcmp(input, "ascii") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (input)  // parametru in plus
		return 0;
	return 1;
}

int check_load_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei load
	// introdus de utilizator este valid, adica formatul sa fie :
	// LOAD NUME NULL (NULL este de la strtok  prin care verificam
	// daca nu mai este un parametru sau, eventual,
	// mai multi, in comanda data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (strcmp(input, "LOAD") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!input)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (input)
		return 0;
	return 1;
}

int check_apply_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei apply
	// introdus de utilizator este valid, adica formatul sa fie :
	// APPLY PARAMETRU NULL (NULL este de la strtok prin care verificam
	// daca nu mai este un parametru sau, eventual,
	// mai multi, in comanda data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (strcmp(input, "APPLY") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!input)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (input)
		return 0;
	return 1;
}

int check_exit_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei exit
	// introdus de utilizator este valid, adica formatul sa fie :
	// EXIT NULL (NULL este de la strtok prin care verificam daca
	// nu mai este un parametru sau, eventual,
	// mai multi, in comanda data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (strcmp(input, "EXIT") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (input)
		return 0;
	return 1;
}

int check_rotate_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei rotate
	// introdus de utilizator este valid, adica formatul sa fie :
	// ROTATE NUMAR NULL (NULL este de la strtok  prin care verificam
	// daca nu mai este un parametru sau, eventual,
	// mai multi, in comanda data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (strcmp(input, "ROTATE") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (!check_number(input))
		return 0;
	return 1;
}

int check_crop_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei crop
	// introdus de utilizator este valid, adica formatul sa fie :
	// CROP NULL (NULL este de la strtok prin care verificam daca nu
	// mai este un parametru sau, eventual,
	// mai multi, in comanda data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (strcmp(input, "CROP") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (input)
		return 0;
	return 1;
}

int check_equalize_command(char command[])
{
	// In aceasta functie verificam daca formatul functiei equalize
	// introdus de utilizator este valid, adica formatul sa fie :
	// EQUALIZE NULL (NULL este de la strtok prin care verificam daca nu
	// mai este un parametru sau, eventual,
	// mai multi, in comanda data de utilizator).
	char copy_command[OPERATION_LEN];
	strcpy(copy_command, command);
	copy_command[(int)strlen(command)] = '\0';
	char *input = strtok(copy_command, SEPARATORS);
	if (strcmp(input, "EQUALIZE") != 0)
		return 0;
	input = strtok(NULL, SEPARATORS);
	if (input)
		return 0;
	return 1;
}

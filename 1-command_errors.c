#include "shell.h"

/**
 * error_string_to_integer - changes a string to integer
 * @st: string to be changed
 * Return: 0  if there are numerical characters in the string
 *		-1 on error
 */
int error_string_to_integer(char *st)
{
	unsigned long int result = 0;
	int a = 0;

	if (*st == '+')
		st++;  /* NB: Skips a leading '+' if present */
	for (a = 0;  st[a] != '\0'; a++)
	{
		if (st[a] >= '0' && st[a] <= '9')
		{
			result = result * 10;
			result += (st[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * display_error - displays err messages
 * @info: The info structure for both parameters and return values
 * @error_st: string holding the specified error type
 * Return: 0  if there are numerical characters in the string
 *		-1 on error
 */
void display_error(info_t *info, char *error_st)
{
	print_error_message(info->fname);
	print_error_message(": ");
	display_decimal(info->line_count, STDERR_FILENO);
	print_error_message(": ");
	print_error_message(info->argv[0]);
	print_error_message(": ");
	print_error_message(error_st);
}

/**
 * display_decimal - Outputs an integer in base 10
 * @number: the input
 * @file_d: the fd to write to
 *
 * Return: number of characters displayed
 */
int display_decimal(int number, int file_d)
{
	int a, count = 0;
	int (*print_character)(char) = print_character;
	unsigned int absolute_value, current_value;

	if (file_d == STDERR_FILENO)
		print_character = print_character_to_fd;
	if (number < 0)
	{
		absolute_value = -number;
		print_character('-');
		count++;
	}
	else
		absolute_value = number;
	current_value = absolute_value;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (absolute_value / a)
		{
			print_character('0' + current_value / a);
			count++;
		}
		current_value %= a;
	}
	print_character('0' + current_value);
	count++;

	return (count);
}

/**
 * convert_to_string - Conversion function, similar to the itoa function
 * @num: number
 * @base: base
 * @flags: flags argument
 *
 * Return: to return string
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *cha_array;
	static char buffer[50];
	char sign = 0, *pt;
	unsigned long converted_value = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		converted_value = -num;
		sign = '-';
	}
	cha_array = flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffer[49];
	*pt = '\0';

	do {
		*--pt = cha_array[converted_value % base];
		converted_value /= base;
	} while (converted_value != 0);

	if (sign)
		*--pt = sign;
	return (pt);
}

/**
 * remove_st_comments - replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_st_comments(char *buffer)
{
	int a;

	for (a = 0; buffer[a] != '\0'; a++)
		if (buffer[a] == '#' && (!a || buffer[a - 1] == ' '))
		{
			buffer[a] = '\0';
			break;
		}
}

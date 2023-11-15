#include "shell.h"

/**
 * interactive_mode - Determines if the shell is in interactive mode
 * @info: Pointer to the info_t struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - Checks if a character is a delimiter
 * @character: The character to check
 * @delimiter_set: The set of delimiters
 *
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char character, char *delimiter_set)
{
	while (*delimiter_set)
	{
		if (*delimiter_set == character)
			return (1);
		delimiter_set++;
	}
	return (0);
}

/**
 * is_alphabetic - Checks if a character is alphabetic
 * @ch: The character to check
 *
 * Return: 1 if 'ch' is alphabetic, 0 otherwise
 */
int is_alphabetic(int ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

/**
 * string_to_integer - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int string_to_integer(char *str)
{
	int i = 0, sign = 1, flag = 0;
	unsigned int result = 0;

	while (str[i] != '\0' && flag != 2)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result = result * 10 + (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
		i++;
	}

	return ((sign == -1) ? -result : result);
}

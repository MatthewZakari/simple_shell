#include "shell.h"

/**
 * find_character - find a char in a string
 * @string: string to be splitted
 * @ch: the char we are to finding
 * Return: a pointer to the first occurrence of the character
 */
char *find_character(char *string, char ch)
{
	do {
		if (*string == ch)
		{
			return (string);
		}
	} while (*string++ != '\0');

	return (NULL);
}

/**
 * concatenate_n - concatenates n characters from source to destination
 * @destination: the initial string
 * @source: the other string
 * @n: the maximum number of bytes to use
 * Return: a pointer to the concatenated string
 */
char *concatenate_n(char *destination, char *source, int n)
{
	int a = 0, b = 0;
	char *result = destination;

	while (destination[a] != '\0')
		a++;
	while (source[b] != '\0' && b < n)
	{
		destination[a] = source[b];
		a++;
		b++;
	}
	if (a < b)
	{
		destination[a] = '\0';
	}
	return (result);
}

/**
 * copy_string_n - copies n characters from source to destination
 * @destination: the destination string to be copied to
 * @source: the source string
 * @n: the maximum number of characters to be copied
 * Return: a pointer to the destination string
 */
char *copy_string_n(char *destination, char *source, int n)
{
	char *result = destination;
	int a = 0, b;

	while (source[a] != '\0' && a < n - 1)
	{
		destination[a] = source[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			destination[b] = '\0';
			b++;
		}
	}
	return (result);
}

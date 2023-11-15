#include "shell.h"

/**
 * copy_string - Creates a copy of a string
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 *
 * Return: Pointer to the duplicated string
 */
char *copy_string(char *dest, const char *src)
{
	int a = -1;

	if (dest == src || src == NULL)
		return (dest);
	do {
		a++;
		dest[a] = src[a];
	} while (src[a] != '\0');

	return (dest);
}

/**
 * duplicate_string - Creates a duplicate of a given string
 * @str: Pointer to the source string to duplicate
 *
 * Return: Pointer to a newly allocated string
 * which is a copy of the source string
 */
char *duplicate_string(const char *str)
{
	char *r;
	int len = 0;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;

	r = malloc(sizeof(char) * (len + 1));

	if (!r)
		return (NULL);

	for (len++; len--;)
		r[len] = *--str;

	return (r);
}

/**
 * print_string - Outputs a string to the console
 * @str: Pointer to the string to be displayed
 *
 * This function prints the characters in the
 * provided string to the standard output.
 * Return: It doesn't return any value.
 */
void print_string(char *str)
{
	int a = 0;

	if (!str)
		return;
	for (a = 0; str[a] != '\0'; a++)
	{
		print_character(str[a]);
	}
}

/**
 * print_character - Sends a character to standard output
 * @ch: The character to be printed
 *
 * Return: Returns 1 on success.
 * On error, returns -1 and sets the appropriate errno.
 */
int print_character(char ch)
{
	static int a;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || a >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, a);
		a = 0;
	}
	if (ch != BUFFER_FLUSH)
		buffer[a++] = ch;
	return (1);
}

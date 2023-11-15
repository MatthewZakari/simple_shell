#include "shell.h"

/**
 * print_st_to_fd - writes the string to a given file descriptor
 * @st: The string to print
 * @file_d: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_st_to_fd(char *st, int file_d)
{
	int a = 0;

	if (!st)
	{
		return (0);
	}

	while (*st)
	{
		a += print_to_fd(*st++, file_d);
	}

	return (a);
}

/**
 * print_to_fd - writes the character to a given file descriptor
 * @ch: The character to print
 * @file_d: The file descriptor to write to
 *
 * Return: 1 on success
 *		-1 on error, and errno is set appropriately.
 */
int print_to_fd(char ch, int file_d)
{
	static int a;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || a >= WRITE_BUFFER_SIZE)
	{
		write(file_d, buffer, a);
		a = 0;
	}

	if (ch != BUFFER_FLUSH)
		buffer[a++] = ch;

	return (1);
}

/**
 * print_character_to_fd - writes the character to a fd(stderr)
 * @ch: The character to print
 *
 * Return: 1 On success
 *		-1 on error, and errno is set appropriately.
 */
int print_character_to_fd(char ch)
{
	static char buffer[WRITE_BUFFER_SIZE];
	static int a;

	if (ch == BUFFER_FLUSH || a >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, a);
		a = 0;
	}

	if (ch != BUFFER_FLUSH)
	{
		buffer[a++] = ch;
	}

	return (1);
}

/**
 * print_error_message - Inputs & prints string
 * @st: the message to be printed
 *
 * Return: NULL
 */
void print_error_message(char *st)
{
	int a = 0;

	if (!st)
		return;

	while (st[a] != '\0')
	{
		print_character_to_fd(st[a]);
		a++;
	}
}

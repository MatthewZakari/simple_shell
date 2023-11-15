#include "shell.h"
/**
 * string_length - Computes the length of a given string.
 * @str: Pointer to the string to be measured.
 *
 * Return: The integer length of the string.
 */
int string_length(char *str)
{
	int len;

	len = 0;
	if (!str)
		return (0);

	while (*str++)
	{
		len++;
	}

	return (len);
}

/**
 * string_compare - Compares two strings lexicographically.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 *
 * Return: - A negative value if str1 is less than str2.
 *		- A positive value if str1 is greater than str2.
 *		- Zero if str1 is equal to str2.
 */
int string_compare(char *str1, char *str2)
{
	for (; *str1 && *str2 && (*str1 == *str2); str1++, str2++)
	{
		/*Continue comparing characters until a difference is found*/
	}

	if (*str1 == *str2)
	{
		return (0); /* Strings are equal */
	}

	return ((*str1 < *str2) ? -1 : 1);
}

/**
 * starts_with_prefix - Determines if the 'needle' string is a
 * prefix of the 'haystack'.
 * @haystack: The string to search within.
 * @needle: The substring to look for at the beginning.
 *
 * Return: Address of the character after the
 * prefix in 'haystack' or NULL if not found.
 */
char *starts_with_prefix(const char *haystack, const char *needle)
{
	for (; *needle != '\0'; needle++, haystack++)
	{
		if (*needle != *haystack)
			return (NULL);
	}

	return ((char *)haystack);
}

/**
 * concatenate_strings - Joins two strings together
 * @dst: The target buffer to which the source string will be appended
 * @sr: The source string that will be added to the target buffer
 *
 * Return: A pointer to the modified destination buffer.
 */
char *concatenate_strings(char *dst, char *sr)
{
	char *result;

	result = dst;
	while (*dst)
		dst++;

	while (*sr)
		*dst++ = *sr++;

	*dst = *sr;

	return (result);
}

#include "shell.h"
/**
 * split_string - Splits an input string into individual
 * words while ignoring consecutive delimiters.
 *
 * @st: The string to be split.
 * @dlim: The string containing delimiters.
 *
 * Return: A pointer to an array of strings containing
 * the split words, or NULL on failure.
 */
char **split_string(char *st, char *dlim)
{
	int i, q, r, s, n_words = 0;
	char **result;

	if (st == NULL || st[0] == 0)
		return (NULL);

	if (!dlim)
		dlim = " ";
	for (i = 0; st[i] != '\0'; i++)
		if (!is_delimiter(st[i], dlim) &&
				(is_delimiter(st[i + 1], dlim) || !st[i + 1]))
			n_words++;

	if (n_words == 0)
		return (NULL);

	result = malloc((1 + n_words) * sizeof(char *));
	if (!result)
		return (NULL);
	for (i = 0, q = 0; q < n_words; q++)
	{
		while (is_delimiter(st[i], dlim))
			i++;
		r = 0;
		while (!is_delimiter(st[i + r], dlim) && st[i + r])
			r++;
		result[q] = malloc((r + 1) * sizeof(char));
		if (!result[q])
		{
			for (r = 0; r < q; r++)
				free(result[r]);
			free(result);
			return (NULL);
		}
		for (s = 0; s < r; s++)
			result[q][s] = st[i++];
		result[q][s] = 0;
	}
	result[q] = NULL;
	return (result);
}

/**
 * split_string2 - Tokenizes a string based on a specified delimiter.
 * @st: The input string to be tokenized.
 * @dlim: The character used as a delimiter.
 *
 * Return: An array of strings representing the tokens, or
 * NULL on failure.
 */
char **split_string2(char *st, char dlim)
{
	int i, q, r, s, n_words = 0;
	char **result;

	if (st == NULL || st[0] == 0)
		return (NULL);

	for (i = 0; st[i] != '\0'; i++)
		if ((st[i] != dlim && st[i + 1] == dlim) ||
				(st[i] != dlim && !st[i + 1]) || st[i + 1] == dlim)
			n_words++;

	if (n_words == 0)
		return (NULL);

	result = malloc((1 + n_words) * sizeof(char *));
	if (!result)
		return (NULL);

	for (i = 0, q = 0; q < n_words; q++)
	{
		while (st[i] == dlim && st[i] != dlim)
			i++;
		r = 0;
		while (st[i + r] != dlim && st[i + r] && st[i + r] != dlim)
			r++;
		result[q] = malloc((r + 1) * sizeof(char));
		if (!result[q])
		{
			for (r = 0; r < q; r++)
				free(result[r]);
			free(result);
			return (NULL);
		}
		for (s = 0; s < r; s++)
			result[q][s] = st[i++];

		result[q][s] = 0;
	}
	result[q] = NULL;
	return (result);
}

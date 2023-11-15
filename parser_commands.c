#include "shell.h"

/**
 * is_command - Checks if a file is an executable command.
 * @info: Pointer to the info struct.
 * @path: file path
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_command(info_t *info, char *path)
{
	(void)info;

	if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
	{
		return (1); /* File exists and is executable */
	}

	return (0); /* file doesn't exist or isn't executable */
}

/**
 * duplicate_chars - Duplicates characters within a range.
 * @source_str: The source string.
 * @start_idx: Starting index.
 * @stop_idx: Stopping index.
 *
 * Return: Pointer to the new buffer.
 */
char *duplicate_chars(char *source_str, int start_idx, int stop_idx)
{
	static char buffer[1024];
	int a = 0, b = 0;

	for (b = 0, a = start_idx; a < stop_idx; a++)
		if (source_str[a] != ':')
		{
			buffer[b++] = source_str[a];
		}
	buffer[b] = 0;
	return (buffer);
}

/**
 * find_path - Finds the command in the PATH string.
 * @info: Pointer to the info struct.
 * @path_str: string PATH
 * @comd: The command to find.
 *
 * Return: Full path of command if found, otherwise NULL.
 */
char *find_path(info_t *info, char *path_str, char *comd)
{
	int pre_pos = 0, a = 0;
	char *p;

	if (!path_str)
		return (NULL);
	if ((string_length(comd) > 2) && starts_with_prefix(comd, "./"))
	{
		if (is_command(info, comd))
			return (comd);
	}
	while (1)
	{
		if (!path_str[a] || path_str[a] == ':')
		{
			p = duplicate_chars(path_str, pre_pos, a);
			if (!*p)
				concatenate_strings(p, comd);
			else
			{
				concatenate_strings(p, "/");
				concatenate_strings(p, comd);
			}
			if (is_command(info, p))
				return (p);
			if (!path_str[a])
				break;
			pre_pos = a;
		}
		a++;
	}
	return (NULL);
}

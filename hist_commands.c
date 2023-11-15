#include "shell.h"

/**
 * get_hist_file - Retrieves the history file path.
 * @info: structure Parameter
 *
 * Return: string holding the history file path.
 */
char *get_hist_file(info_t *info)
{
	char *buffer, *d;

	d = get_env_var(info, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (string_length(d) + string_length(HISTORY_FILE)
				+ 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	copy_string(buffer, d);
	concatenate_strings(buffer, "/");
	concatenate_strings(buffer, HISTORY_FILE);
	return (buffer);
}

/**
 * hist_write - Writes history to a file.
 * @info: Parameter structure.
 *
 * Return: 1 on success or -1 on error.
 */
int hist_write(info_t *info)
{
	list_t *node = NULL;
	ssize_t file_d;
	char *file_n = get_hist_file(info);

	if (!file_n)
		return (-1);

	file_d = open(file_n, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_n);
	if (file_d == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		print_st_to_fd(node->st, file_d);
		print_to_fd('\n', file_d);
	}
	print_to_fd(BUFFER_FLUSH, file_d);
	close(file_d);
	return (1);
}

/**
 * hist_read - Reads history from a file.
 * @info: Parameter structure.
 *
 * Return: Number of history entries read on success, 0 otherwise.
 */
int hist_read(info_t *info)
{
	struct stat sta;
	char *buffer = NULL, *file_n = get_hist_file(info);
	int linecount = 0, a, lst = 0;
	ssize_t file_d, readlen, file_size = 0;

	if (!file_n)
		return (0);

	file_d = open(file_n, O_RDONLY);
	free(file_n);
	if (file_d == -1)
		return (0);
	if (!fstat(file_d, &sta))
		file_size = sta.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	readlen = read(file_d, buffer, file_size);
	buffer[file_size] = 0;
	if (readlen <= 0)
		return (free(buffer), 0);
	close(file_d);
	for (a = 0; a < file_size; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			hist_build(info, buffer + lst, linecount++);
			lst = a + 1;
		}
	if (lst != a)
		hist_build(info, buffer + lst, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= MAX_HISTORY_ENTRIES)
		del_node_at_index(&(info->history), 0);
	hist_renumb(info);
	return (info->histcount);
}

/**
 * hist_build - Adds entry to the linked list of hist.
 * @info: Parameter structure.
 * @buffer: Buffer containing history entry.
 * @linecount: The history linecount.
 *
 * Return: 0 Always
 */
int hist_build(info_t *info, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (info->history)
	{
		node = info->history;
	}
	add_node_to_end(&node, buffer, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * hist_renumb - After changes it renumbers the history linked list
 * @info: Parameter structure.
 *
 * Return: new histcount.
 */
int hist_renumb(info_t *info)
{
	list_t *node;
	int a = 0;

	node = info->history;
	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}

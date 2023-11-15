#include "shell.h"

/**
 * handle_signal - Handles the interrupt signal(blocks ctrl-C)
 * @s_num: signal number
 *
 * Return: Void
 */
void handle_signal(__attribute__((unused))int s_num)
{
	print_string("\n");
	print_string("$ ");
	print_character(BUFFER_FLUSH);
}

/**
 * custom_getline - Gets the next line of input from STDIN
 * @info: A struct that holds parameters
 * @pt: pointer to the buffer address, NULL or preallocated
 * @len: if not buffer not NULL, Size of the preallocated buffer
 *
 * Return: The number of bytes read
 */
int custom_getline(info_t *info, char **pt, size_t *len)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t a, l;
	size_t g;
	ssize_t bytes_read = 0, t_bytes = 0;
	char *q = NULL, *q_new = NULL, *b;

	q = *pt;
	if (q && len)
		t_bytes = *len;
	if (a == l)
		a = l = 0;

	bytes_read = read_buffer(info, buffer, &l);
	if (bytes_read == -1 || (bytes_read == 0 && l == 0))
		return (-1);

	b = find_character(buffer + a, '\n');
	g = b ? 1 + (unsigned int)(b - buffer) : l;
	q_new = reallocate_mem(q, t_bytes, t_bytes ? t_bytes + g : g + 1);

	if (!q_new)
		return (q ? free(q), -1 : -1);

	if (t_bytes)
		concatenate_n(q_new, buffer + a, g - a);
	else
		copy_string_n(q_new, buffer + a, g - a + 1);

	t_bytes += g - a;
	a = g;
	q = q_new;
	if (len)
		*len = t_bytes;
	*pt = q;

	return (t_bytes);
}

/**
 * _get_input - Gets a line without the newline character
 * @info: A struct that holds parameters
 *
 * Return: Number of bytes read
 */
ssize_t _get_input(info_t *info)
{
	char **cmd_buf_ptr = &(info->arg);
	ssize_t bytes_read = 0;
	static size_t a, b, chain_len;
	static char *cmd_buf;
	char *current_cmd;

	print_character(BUFFER_FLUSH);
	bytes_read = buffer_input(info, &cmd_buf, &chain_len);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (chain_len)
	{
		b = a;
		current_cmd = cmd_buf + a;

		check_cmd_chain(info, cmd_buf, &b, a, chain_len);
		while (b < chain_len)
		{
			if (is_cmd_chained(info, cmd_buf, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= chain_len)
		{
			a = chain_len = 0;  /*position & length reset*/
			info->cmd_buf_type = CMD_NORMAL;
		}

		*cmd_buf_ptr = current_cmd;
		return (string_length(current_cmd));
	}

	*cmd_buf_ptr = cmd_buf;
	return (bytes_read);
}

/**
 * read_buffer - buffer reader
 * @info: A struct that holds parameters
 * @buffer: The buffer
 * @len: The size
 *
 * Return: Number of bytes read
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *len)
{
	ssize_t bytes_read = 0;

	if (*len)
		return (0);
	bytes_read = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (bytes_read >= 0)
		*len = bytes_read;
	return (bytes_read);
}

/**
 * buffer_input - Chained buffer cmds
 * @info: A struct that holds parameters
 * @buffer: Address of the buffer
 * @l: Address of the length variable
 *
 * Return: Number of bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *l)
{
	size_t plength = 0;
	ssize_t bytes_read = 0;

	if (!*l) /* fill buffer if there's nothing left */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_signal);
#if USE_GETLINE
		bytes_read = getline(buffer, &plength, stdin);
#else
		bytes_read = custom_getline(info, buffer, &plength);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_st_comments(*buffer);
			hist_build(info, *buffer, info->histcount++);
			if (find_character(*buffer, ';'))
			{
				*l = bytes_read;
				info->cmd_buffer = buffer;
			}
		}
	}

	return (bytes_read);
}

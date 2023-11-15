#include "shell.h"

/**
 * is_cmd_chained - Determines if the current character in
 * the buffer serves as a command chaining delimiter
 * @info: Pointer to the parameter struct
 * @buffer: Character buffer
 * @q: Address of the current position in buf
 *
 * Return: 1 if it is a command chaining delimiter, 0 otherwise
 */
int is_cmd_chained(info_t *info, char *buffer, size_t *q)
{
	size_t g = *q;

	if (buffer[g] == '|' && buffer[g + 1] == '|')
	{
		buffer[g] = 0;
		g++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[g] == '&' && buffer[g + 1] == '&')
	{
		buffer[g] = 0;
		g++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[g] == ';')
	{
		buffer[g] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = g;
	return (1);
}

/**
 * check_cmd_chain - Determines whether we should continue
 * chaining based on the previous status
 *
 * @info: Pointer to the parameter struct
 * @buffer: Character buffer
 * @q: Address of the current position in buf
 * @s: Starting index in buf
 * @l: Length of buffer
 *
 * Returns: None
 */
void check_cmd_chain(info_t *info, char *buffer, size_t *q, size_t s, size_t l)
{
	size_t g = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[s] = 0;
			g = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[s] = 0;
			g = l;
		}
	}
	*q = g;
}

/**
 * rep_alias - Substitutes aliases in the tokenized string
 * @info: Pointer to the parameter structure
 *
 * Return: 1 if substitutions were made, 0 otherwise
 */
int rep_alias(info_t *info)
{
	char *q;
	int a;
	list_t *node;

	for (a = 0; a < 10; a++)
	{
		node = node_with_prefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		q = find_character(node->st, '=');
		if (!q)
			return (0);
		q = duplicate_string(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * rep_var - Substitutes variables in the tokenized string
 * @info: Pointer to the parameter structure
 *
 * Return: 1 if substitution successful, 0 otherwise
 */
int rep_var(info_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!string_compare(info->argv[a], "$?"))
		{
			rep_buf_strg(&(info->argv[a]),
					duplicate_string(convert_to_string(info->status, 10, 0)));
			continue;
		}
		if (!string_compare(info->argv[a], "$$"))
		{
			rep_buf_strg(&(info->argv[a]),
					duplicate_string(convert_to_string(getpid(), 10, 0)));
			continue;
		}
		node = node_with_prefix(info->env, &info->argv[a][1], '=');
		if (node)
		{
			rep_buf_strg(&(info->argv[a]),
					duplicate_string(find_character(node->st, '=') + 1));
			continue;
		}
		rep_buf_strg(&info->argv[a], duplicate_string(""));
	}
	return (0);
}

/**
 * rep_buf_strg - Updates a buffer string
 * @o: Address of the original string
 * @n: New string value
 *
 * Return: 1 if successful, 0 otherwise
 */
int rep_buf_strg(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}

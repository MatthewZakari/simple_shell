#include "shell.h"

/**
 * display_history - Display the command hist, 1 command per line, along
 * with line numbers starting from 0.
 * @info: Structure containing potential arguments and history info
 *
 * Return: Always returns 0.
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * m_unset_alias - Unset an alias specified by its name.
 * @info: Parameter structure containing alias information.
 * @st: The name of the alias to unset.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int m_unset_alias(info_t *info, char *st)
{
	char *equal_sign, temp_char;
	int result;

	equal_sign = find_character(st, '=');
	if (!equal_sign)
		return (1);

	temp_char = *equal_sign;
	*equal_sign = '\0';

	result = del_node_at_index(&(info->alias),
			get_index_node(info->alias, node_with_prefix(info->alias, st, -1)));

	*equal_sign = temp_char;
	return (result);
}

/**
 * m_set_alias - Set an alias to a specified string.
 * @info: Parameter structure containing alias information.
 * @st: The string to set as an alias.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int m_set_alias(info_t *info, char *st)
{
	char *equal_sign;

	equal_sign = find_character(st, '=');
	if (!equal_sign)
		return (1);

	if (!*++equal_sign)
		return (m_unset_alias(info, st));

	m_unset_alias(info, st);
	return (add_node_to_end(&(info->alias), st, 0) == NULL);
}

/**
 * p_alias - Print the specified alias.
 * @node: The alias node to be printed.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int p_alias(list_t *node)
{
	char *equal_sign, *c;

	if (node == NULL)
		return (1);
	equal_sign = find_character(node->st, '=');
	if (equal_sign)
	{
		for (c = node->st; c <= equal_sign; c++)
			print_character(*c);
		print_character('\'');
		print_string(equal_sign + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * display_alias - Mimics the behavior of the alias
 * builtin command (man alias).
 * @info: Structure containing potential arguments and alias information.
 *
 * Return: Always returns 0.
 */
int display_alias(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			p_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = find_character(info->argv[i], '=');
		if (equal_sign)
			m_set_alias(info, info->argv[i]);
		else
			p_alias(node_with_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}

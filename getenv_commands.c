#include "shell.h"

/**
 * set_env_var - Sets or modifies an environment variable
 * @info: Structure containing relevant information.
 * @var: The name of the environment variable.
 * @value: The value to be assigned to the environment variable.
 * Return: Always returns 0.
 */
int set_env_var(info_t *info, char *var, char *value)
{
	list_t *node;
	char *q, *buffer = NULL;

	if (!var || !value)
		return (0);

	buffer = malloc(string_length(var) + string_length(value) + 2);
	if (!buffer)
		return (1);
	copy_string(buffer, var);
	concatenate_strings(buffer, "=");
	concatenate_strings(buffer, value);
	node = info->env;
	while (node)
	{
		q = starts_with_prefix(node->st, var);
		if (q && *q == '=')
		{
			free(node->st);
			node->st = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_to_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

/**
 * unset_env_var - Removes an environ var
 * @info: Structure that contains the relevant information.
 * @var: The name of the environment variable to be removed.
 * Return: 1 if variable is deleted, 0 otherwise.
 */
int unset_env_var(info_t *info, char *var)
{
	size_t a = 0;
	char *q;
	list_t *node = info->env;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with_prefix(node->st, var);
		if (q && *q == '=')
		{
			info->env_changed = del_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * get_envron_var - Retrieves the environment variables as a string array
 * @info: Structure containing relevant information.
 * Return: Pointer to the environment variables array.
 */
char **get_envron_var(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

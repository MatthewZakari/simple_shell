#include "shell.h"

/**
 * pop_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int pop_env_list(info_t *info)
{
	size_t a;
	list_t *node = NULL;

	for (a = 0; environ[a]; a++)
		add_node_to_end(&node, environ[a], 0);

	info->env = node;
	return (0);
}

/**
 * m_unset_env_var - deletes an environ var.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int m_unset_env_var(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		print_error_message("Arguments too few.\n");
		return (1);
	}
	for (a = 1; a < info->argc; a++)
	{
		unset_env_var(info, info->argv[a]);
	}
	return (0);
}

/**
 * m_set_env_var - Modifies an existing one or
 * Initializes a new environment variable
 * @info: Structure containing potential arguments.
 * Return: 1 on success, 0 on failure.
 */
int m_set_env_var(info_t *info)
{
	if (info->argc != 3)
	{
		print_error_message("Number of arguments incorrect.\n");
		return (1);
	}

	if (set_env_var(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * get_env_var - Gets environment variable value.
 * @info: Structure containing potential arguments.
 * @name: Name of the environment variable.
 * Return: The value of the variable, or NULL if not found.
 */
char *get_env_var(info_t *info, const char *name)
{
	char *value;
	list_t *node = info->env;

	while (node)
	{
		value = starts_with_prefix(node->st, name);
		if (value && *value)
			return (value);
		node = node->next;
	}

	return (NULL);
}

/**
 * display_environment - Displays the present environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int display_environment(info_t *info)
{
	print_list_of_strings(info->env);
	return (0);
}

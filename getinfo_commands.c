#include "shell.h"

/**
 * del_info - deallocates memory used by info_t struct
 * @info: address of the struct
 */
void del_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * put_info - populates info_t struct with arguments
 * @info: address of the struct
 * @argvec: vector argument
 */
void put_info(info_t *info, char **argvec)
{
	int a = 0;

	info->fname = argvec[0];
	if (info->arg)
	{
		info->argv = split_string(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicate_string(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		rep_alias(info);
		rep_var(info);
	}
}

/**
 * release_info - releases resources used by info_t struct
 * @info: address of the struct
 * @r_all: true if releasing all resources
 */
void release_info(info_t *info, int r_all)
{
	free_mem(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (r_all)
	{
		if (!info->cmd_buffer)
			free(info->arg);
		if (info->env)
			free_linked_list(&(info->env));
		if (info->history)
			free_linked_list(&(info->history));
		if (info->alias)
			free_linked_list(&(info->alias));
		free_mem(info->environ);
		info->environ = NULL;
		b_free((void **)info->cmd_buffer);
		if (info->readfd > 2)
			close(info->readfd);
		print_character(BUFFER_FLUSH);
	}
}

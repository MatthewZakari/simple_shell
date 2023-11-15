#include "shell.h"

/**
 * shell_loop - Main shell loop
 * @info: Pointer to the info struct
 * @arg_v: Argument vector from main()
 *
 * Return: 0 on success
 *		- 1 on error
 *		- Error code
 */
int shell_loop(info_t *info, char **arg_v)
{
	ssize_t read_status = 0;
	int builtin_result = 0;

	while (read_status != -1 && builtin_result != -2)
	{
		del_info(info);

		if (interactive_mode(info))
			print_string("$ ");

		print_character_to_fd(BUFFER_FLUSH);
		read_status = _get_input(info);

		if (read_status != -1)
		{
			put_info(info, arg_v);
			builtin_result = find_builtin_command(info);
			if (builtin_result == -1)
				find_command(info);
		}
		else if (interactive_mode(info))
		{
			print_character('\n');
		}
		release_info(info, 0);
	}
	hist_write(info);
	release_info(info, 1);

	if (!interactive_mode(info) && info->status)
		exit(info->status);

	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin_command - Looks for  builtin command
 * @info: info struct pointer
 *
 * Return: builtin not found, return 1
 *	builtin execute success, return 0
 *	builtin found but didn't esxecute, return 1,
 *	builtin signals exit(), return 2
 */
int find_builtin_command(info_t *info)
{
	int a = 0;
	int built_in_result = -1;

	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", display_environment},
		{"help", display_help},
		{"history", display_history},
		{"setenv",  m_set_env_var},
		{"unsetenv", m_unset_env_var},
		{"cd", change_directory},
		{"alias", display_alias},
		{NULL, NULL}
	};

	while (builtintbl[a].type)
	{
		if (string_compare(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			built_in_result = builtintbl[a].func(info);
			break;
		}
		a++;
	}

	return (built_in_result);
}

/**
 * find_command - looks for a command in PATH
 * @info: info struct pointer
 *
 * Returns: void
 */
void find_command(info_t *info)
{
	int a, b;
	char *path = NULL;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (a = 0, b = 0; info->arg[a]; a++)
		if (!is_delimiter(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(info, get_env_var(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((interactive_mode(info) || get_env_var(info, "PATH=")
					|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
		{
			fork_command(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			display_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - Initiates a new execution thread to run the command
 * @info: info struct pointer
 *
 * Returns: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_envron_var(info)) == -1)
		{
			release_info(info, 1);

			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				display_error(info, "Permission denied\n");
		}
	}
}

#include "shell.h"

/**
 * exit_shell - Exits the shell
 * @info: Structure containing potential arguments
 *
 * Return: Exits with a given exit status or returns 0
 */
int exit_shell(info_t *info)
{
	int exit_code;
	char c_str[2];/*char array to hold the char &  '\0' char*/

	if (info->arg[1])
	{
		c_str[0] = info->arg[1];
		c_str[1] = '\0';/*Null-terminate the char array*/

		exit_code = error_string_to_integer(c_str);
		if (exit_code == -1)
		{
			info->status = 2;
			display_error(info, "Illegal number: ");
			print_error_message(c_str);
			print_character_to_fd('\n');
			return (1);
		}
		info->err_num = exit_code;
	}
	else
		info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Changes the current directory of the process
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int change_directory(info_t *info)
{
	char buffer[1024];
	char *current_dir = getcwd(buffer, sizeof(buffer));
	char *home_dir = get_env_var(info, "HOME=");
	char *pwd_dir = get_env_var(info, "PWD=");
	int chdir_ret;
	char *new_dir = new_dir = info->argv[1] ? info->argv[1]
		: (home_dir ? home_dir	: (pwd_dir ? pwd_dir : "/"));

	if (new_dir[0] == '-')
	{
		new_dir = get_env_var(info, "OLDPWD=");
		if (!new_dir)
		{
			print_string(current_dir);
			print_character('\n');
			return (1);
		}
		print_string(new_dir);
		print_character('\n');
	}
	chdir_ret = chdir(new_dir);
	if (chdir_ret == -1)
	{
		display_error(info, "can not cd to ");
		print_character_to_fd(new_dir[0]);
		print_character('\n');
	}
	else
	{
		set_env_var(info, "OLDPWD", get_env_var(info, "PWD="));
		set_env_var(info, "PWD", getcwd(buffer, sizeof(buffer)));
	}

	return (0);
}

/**
 * display_help - Modifies the current working directory of the process.
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int display_help(info_t *info)
{
	char *arg_array;

	arg_array = info->arg;
	print_string("Help call works. Function not yet implemented\n");
	if (0)
		print_string(arg_array);
	return (0);
}

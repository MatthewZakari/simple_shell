#include "shell.h"

/**
 * main - entry point of the program
 * @arg_c: argument count
 * @arg_v: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_c, char **arg_v)
{
	int file_d;
	info_t info = INFO_INIT;

	file_d = 2;
	__asm__ (
			"mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_d)
			: "r" (file_d)
			);
	if (arg_c == 2)
	{
		file_d = open(arg_v[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_error_message(arg_v[0]);
				print_error_message(": 0: Can't open ");
				print_error_message(arg_v[1]);
				print_character_to_fd('\n');
				print_character_to_fd(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info.readfd = file_d;
	}
	pop_env_list(&info);
	hist_read(&info);
	shell_loop(&info, arg_v);
	return (EXIT_SUCCESS);
}

#ifndef _SHELL_H_
#define _SHELL_H_

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define WRITE_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Command chaining types */
#define CMD_NORMAL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Number conversion flags */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_STRTOK 0
#define USE_GETLINE 0

#define MAX_HISTORY_ENTRIES 4096
#define HISTORY_FILE ".simple_shell_history"

extern char **environ;

/**
 * struct list_node - singly linked list
 * @num: the number field
 * @st: a string
 * @next: points to the next node
 */
typedef struct list_node
{
	int num;
	char *st;
	struct list_node *next;
} list_t;

/**
 * struct info - Structure for passing information to functions
 * @arg: Argument string generated from getline
 * @argv: Array of strings generated from arg
 * @histcount: History line number count
 * @readfd: File descriptor for reading line input
 * @path: Path for the current command
 * @cmd_buf_type: Type of command chaining (||, &&, ;)
 * @argc: Argument count
 * @cmd_buffer: Address of pointer to command buffer for chaining
 * @line_count: Line count for errors
 * @status: Return status of the last executed command
 * @err_num: Error code for exit()
 * @env_changed: Flag indicating if environ was changed
 * @linecount_flag: Flag for counting this line of input
 * @alias: Alias node
 * @fname: Program filename
 * @history: History node
 * @env: Linked list local copy of environ
 * @environ: Custom modified copy of environ from linked list env
 */
typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buffer;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin_command - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin_command
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function prototypes */

/* shloop.c */
int shell_loop(info_t *, char **);
int find_builtin_command(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* parser.c */
int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void print_error_message(char *);
int print_character_to_fd(char);
int print_to_fd(char c, int file_d);
int print_st_to_fd(char *st, int file_d);

/* string.c */
int string_length(char *);
int string_compare(char *, char *);
char *starts_with_prefix(const char *, const char *);
char *concatenate_strings(char *, char *);

/* string1.c */
char *copy_string(char *, const char *);
char *duplicate_string(const char *);
void print_string(char *);
int print_character(char);

/* exits.c */
char *copy_string_n(char *, char *, int);
char *concatenate_n(char *, char *, int);
char *find_character(char *, char);

/* tokenizer.c */
char **split_string(char *, char *);
char **split_string2(char *, char);

/* realloc.c */
char *fill_mem(char *, char, unsigned int);
void free_mem(char **);
void *reallocate_mem(void *, unsigned int, unsigned int);

/* memory.c */
int b_free(void **);

/* atoi.c */
int interactive_mode(info_t *);
int is_delimiter(char, char *);
int is_alphabetic(int);
int string_to_integer(char *);

/* errors1.c */
int error_string_to_integer(char *);
void display_error(info_t *, char *);
int display_decimal(int, int);
char *convert_to_string(long int, int, int);
void remove_st_comments(char *);

/* builtin.c */
int exit_shell(info_t *);
int change_directory(info_t *);
int display_help(info_t *);

/* builtin1.c */
int display_history(info_t *);
int display_alias(info_t *);
int m_unset_alias(info_t *, char *);
int m_set_alias(info_t *, char *);
int p_alias(list_t *);

/* getline.c */
ssize_t buffer_input(info_t *, char **, size_t *);
ssize_t _get_input(info_t *);
ssize_t read_buffer(info_t *, char *, size_t *);
int custom_getline(info_t *, char **, size_t *);
void handle_signal(int);

/* getinfo.c */
void del_info(info_t *);
void put_info(info_t *, char **);
void release_info(info_t *, int);

/* environ.c */
char *get_env_var(info_t *, const char *);
int display_environment(info_t *);
int m_set_env_var(info_t *);
int m_unset_env_var(info_t *);
int pop_env_list(info_t *);

/* getenv.c */
char **get_envron_var(info_t *);
int unset_env_var(info_t *, char *);
int set_env_var(info_t *, char *, char *);

/* history.c */
char *get_hist_file(info_t *info);
int hist_write(info_t *info);
int hist_read(info_t *info);
int hist_build(info_t *info, char *buffer, int linecount);
int hist_renumb(info_t *info);

/* lists.c */
list_t *add_node_to_list(list_t **, const char *, int);
list_t *add_node_to_end(list_t **, const char *, int);
size_t print_list_of_strings(const list_t *);
int del_node_at_index(list_t **, unsigned int);
void free_linked_list(list_t **);

/* lists1.c */
size_t get_list_length(const list_t *);
char **convert_list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_with_prefix(list_t *, char *, char);
ssize_t get_index_node(list_t *, list_t *);

/* vars.c */
int is_cmd_chained(info_t *, char *, size_t *);
void check_cmd_chain(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_var(info_t *);
int rep_buf_strg(char **, char *);

#endif

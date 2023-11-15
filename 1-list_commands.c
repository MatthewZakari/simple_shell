#include "shell.h"

/**
 * get_list_length - determines the length of a linked list
 * @list: first node pointer
 *
 * Return: list size
 */
size_t get_list_length(const list_t *list)
{
	size_t count;

	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}

/**
 * convert_list_to_strings - brings an array of strings from list->str
 * @head: first node pointer
 *
 * Return: array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	char **strings, *string;
	list_t *current_node = head;
	size_t a, length = get_list_length(head);

	if (!head || !length)
		return (NULL);

	strings = malloc(sizeof(char *) * (length + 1));
	if (!strings)
		return (NULL);

	for (a = 0; current_node; current_node = current_node->next, a++)
	{
		string = malloc(string_length(current_node->st) + 1);
		if (!string)
		{
			for (a = 0; a < length; a++)
				free(strings[a]);
			free(strings);
			return (NULL);
		}

		string = copy_string(string, current_node->st);
		strings[length] = string;
	}
	strings[length] = NULL;
	return (strings);
}

/**
 * print_list - writes every elements of a list_t linked list
 * @list: first node pointer
 *
 * Return: list size
 */
size_t print_list(const list_t *list)
{
	size_t count = 0;

	while (list)
	{
		print_string(convert_to_string(list->num, 10, 0));
		print_character(':');
		print_character(' ');
		print_string(list->st ? list->st : "(nil)");
		print_string("\n");
		list = list->next;
		count++;
	}
	return (count);
}

/**
 * node_with_prefix - returns node whose string starts with prefix
 * @list: list head ptr
 * @prefix: the string to match
 * @ch: next char after prefix to match
 *
 * Return: matching node or null
 */
list_t *node_with_prefix(list_t *list, char *prefix, char ch)
{
	char *q = NULL;

	while (list)
	{
		q = starts_with_prefix(list->st, prefix);
		if (q && ((ch == -1) || (*q == ch)))
			return (list);
		list = list->next;
	}
	return (NULL);
}

/**
 * get_index_node - finds the index of a node
 * @head: list head pointer
 * @node: node pointer
 *
 * Return: index of node or -1
 */
ssize_t get_index_node(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

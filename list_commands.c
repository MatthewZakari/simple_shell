#include "shell.h"

/**
 * add_node_to_list - Inserts new node at the beginning of a linked list.
 * @list: Address of pointer to the head node.
 * @st: String field of the new node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the newly added node.
 */
list_t *add_node_to_list(list_t **list, const char *st, int num)
{
	list_t *new_list;

	if (!list)
		return (NULL);
	new_list = malloc(sizeof(list_t));
	if (!new_list)
		return (NULL);
	fill_mem((void *)new_list, 0, sizeof(list_t));
	new_list->num = num;
	if (st)
	{
		new_list->st = duplicate_string(st);
		if (!new_list->st)
		{
			free(new_list);
			return (NULL);
		}
	}

	new_list->next = *list;
	*list = new_list;
	return (new_list);
}

/**
 * add_node_to_end - Appends a new node at the end of a linked list.
 * @list: pointer address to the head node.
 * @str: String field of the new node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the newly added node.
 */
list_t *add_node_to_end(list_t **list, const char *str, int num)
{
	list_t *new_list, *node;

	if (!list)
		return (NULL);

	node = *list;
	new_list = malloc(sizeof(list_t));
	if (!new_list)
		return (NULL);

	fill_mem((void *)new_list, 0, sizeof(list_t));
	new_list->num = num;

	if (str)
	{
		new_list->st = duplicate_string(str);
		if (!new_list->st)
		{
			free(new_list);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_list;
	}
	else
		*list = new_list;
	return (new_list);
}

/**
 * print_list_of_strings - Prints the string element only of a
 * list_t linked list.
 * @list: Pointer to the first node.
 *
 * Return: list size
 */
size_t print_list_of_strings(const list_t *list)
{
	size_t count = 0;

	while (list)
	{
		print_string(list->st ? list->st : "(nil)");
		print_string("\n");
		list = list->next;
		count++;
	}
	return (count);
}

/**
 * del_node_at_index - Deletes the node at a specified index.
 * @list: pointer address to the initial node.
 * @index: Index of the node to be deleted.
 *
 * Return: 1 on success, 0 on failure.
 */
int del_node_at_index(list_t **list, unsigned int index)
{
	unsigned int a = 0;
	list_t *node, *prior_node;

	if (!list || !*list)
		return (0);

	if (!index)
	{
		node = *list;
		*list = (*list)->next;
		free(node->st);
		free(node);
		return (1);
	}

	node = *list;
	while (node)
	{
		if (a == index)
		{
			prior_node->next = node->next;
			free(node->st);
			free(node);
			return (1);
		}
		a++;
		prior_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_linked_list - Frees every nodes of a linked list.
 * @list_pt: pointer address to the head node.
 *
 * Return: void.
 */
void free_linked_list(list_t **list_pt)
{
	list_t *list, *node, *n_node;

	if (!list_pt || !*list_pt)
		return;

	list = *list_pt;
	node = list;

	while (node)
	{
		n_node = node->next;
		free(node->st);
		free(node);
		node = n_node;
	}
	*list_pt = NULL;
}

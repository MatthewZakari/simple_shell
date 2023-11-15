#include "shell.h"
/**
 * fill_mem - fill up the mem with a constant byte
 * @dest: memory area pointer
 * @ch: the byte to fill *dest with
 * @n: bytes amount to be filled
 *
 * Return: dest
 */
char *fill_mem(char *dest, char ch, unsigned int n)
{
	char *ptr = dest;

	while (n--)
	{
		*ptr++ = ch;
	}

	return (dest);
}

/**
 * free_mem - frees str of strs
 * @str_arr: str of strs
 */
void free_mem(char **str_arr)
{
	char **temp;

	if (!str_arr || !*str_arr)
		return;

	for (temp = str_arr; *temp; temp++)
	{
		free(*temp);
	}

	free(str_arr);
}

/**
 * reallocate_mem - reallocates a block of memory
 * @ptr: previous malloced block pointer
 * @p_size: previous block's byte
 * @n_size: new block's byte
 *
 * Return: pointer to the reallocated block of memory.
 */
void *reallocate_mem(void *ptr, unsigned int p_size, unsigned int n_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr), NULL);
	if (n_size == p_size)
		return (ptr);

	new_ptr = malloc(n_size);
	if (!new_ptr)
		return (NULL);
	p_size = p_size < n_size ? p_size : n_size;
	while (p_size--)
		new_ptr[p_size] = ((char *)ptr)[p_size];
	free(ptr);
	return (new_ptr);
}

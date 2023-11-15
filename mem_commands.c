#include "shell.h"
/**
 * b_free - Frees a pointer and sets it to NULL
 * @p_ptr: pointer address to free
 *
 * This function takes the address of a pointer as an argument.
 * It checks if the pointer is not NULL and if
 * the memory it points to is allocated.
 * If so, it frees the memory and sets the pointer to NULL.
 *
 * Return: 1 if memory is freed, otherwise 0.
 */
int b_free(void **p_ptr)
{
	if (p_ptr == NULL || *p_ptr == NULL)
	{
		return (0);
	}
	free(*p_ptr);
	*p_ptr = NULL;
	return (1);
}

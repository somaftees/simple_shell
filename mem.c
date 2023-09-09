#include "main.h"

/**
 * _memcpy - a function that copies information between void pointers.
 * @newptr: void.
 * @ptr: const void.
 * @size: unsigned integer.
 * Return: void.
 */

void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *ch_ptr = (char *)ptr;
	char *ch_new_ptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		ch_new_ptr[i] = ch_ptr[i];
}

/**
 * _realloc - a function that reallocates a memory block.
 * @ptr: void pointer.
 * @old_size: unsigned integer.
 * @new_size: unsigned integer.
 * Return: pointer.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(new_ptr, ptr, new_size);
	else
		_memcpy(new_ptr, ptr, old_size);

	free(ptr);
	return (new_ptr);
}

/**
 * _reallocdp - a function that reallocates a memory block of a double pointer.
 * @ptr: char pointer.
 * @old_size: unsigned integer.
 * @new_size: unsigned integer.
 * Return: pointer.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **new_ptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(sizeof(char *) * new_size);
	if (new_ptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		new_ptr[i] = ptr[i];

	free(ptr);

	return (new_ptr);
}

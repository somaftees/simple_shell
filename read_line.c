#include "main.h"

/**
 * read_line - reads input
 *
 * @i_eof: return value of getline
 * Return: input string
 */
char *read_line(int *i_eof)
{
	char *in = NULL;
	size_t buf_size = 0;

	*i_eof = getline(&in, &buf_size, stdin);

	return (in);
}

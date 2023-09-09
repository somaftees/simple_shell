#include "main.h"

/**
 * bring_line - a function that assigns 
 * the line var for get_line
 * @lineptr: a char.
 * @buffer: a char.
 * @n: size_t.
 * @j: size_t.
 */

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * get_line - a functoin that reads input from stream.
 * @lineptr: a char.
 * @n: size_t.
 * @stream: FILE.
 * Return: -1 or number of bytes.
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t ipt;
	ssize_t r;
	char *b;
	char x= 'z';

	if (ipt == 0)
		fflush(stream);
	else
		return (-1);
	ipt = 0;

	b = malloc(sizeof(char) * BUFSIZE);
	if (b == 0)
		return (-1);
	while (x!= '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && ipt == 0))
		{
			free(b);
			return (-1);
		}
		if (i == 0 && ipt != 0)
		{
			ipt++;
			break;
		}
		if (ipt >= BUFSIZE)
			b = _realloc(b, ipt, ipt + 1);
		b[ipt] = t;
		ipt++;
	}
	b[ipt] = '\0';
	bring_line(lineptr, n, b, ipt);
	r = ipt;
	if (i != 0)
		ipt = 0;
	return (r);
}

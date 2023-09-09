#include "main.h"

/**
 * bring_line - a function that asigns
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
	static ssize_t in;
	ssize_t h;
	char *buffer;
	char t = 'z';

	if (in == 0)
		fflush(stream);
	else
		return (-1);
	in = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && in == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && in != 0)
		{
			in++;
			break;
		}
		if (in >= BUFSIZE)
			buffer = _realloc(buffer, in, in + 1);
		buffer[in] = t;
		in++;
	}
	buffer[in] = '\0';
	bring_line(lineptr, n, buffer, in);
	h = in;
	if (i != 0)
		in = 0;
	return (h);
}

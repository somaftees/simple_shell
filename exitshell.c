#include "main.h"

/**
 * exit_shell - a function that exits the shell.
 * @datash: data_shell.
 * Return: 0 or 1.
 */
int exit_shell(data_shell *datash)
{
	unsigned int s;
	int digital;
	int slen;
	int max;

	if (datash->args[1] != NULL)
	{
		s = _atoi(datash->args[1]);
		digital = _isdigit(datash->args[1]);
		slen = _strlen(datash->args[1]);
		max = s > (unsigned int)INT_MAX;
		if (!digital || slen > 10 || max)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (s % 256);
	}
	return (0);
}

#include "main.h"

/**
 * without_comment - a function that deletes comments from the input.
 * @in: a char.
 * Return: a char.
 */
char *without_comment(char *in)
{
	int i, k;

	k = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				k = i;
		}
	}

	if (k != 0)
	{
		in = _realloc(in, i, k + 1);
		in[k] = '\0';
	}

	return (in);
}

/**
 * shell_loop - the loop of the Shell :)
 * @datash: data_shell.
 * Return: void.
 */
void shell_loop(data_shell *datash)
{
	int h, i;
	char *input;

	h = 1;
	while (h == 1)
	{
		write(STDIN_FILENO, "($) ", 4);
		input = read_line(&i);
		if (i != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			h = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			h = 0;
			free(input);
		}
	}
}

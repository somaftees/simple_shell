#include "main.h"

/**
 * repeated_char - a function that counts the repetitions of a char.
 * @input: char.
 * @i: integer.
 * Return: value.
 */

int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - a function that finds syntax errors.
 * @input: char
 * @i: integer.
 * @last: char.
 * Return: i or value
 */
int error_sep_op(char *input, int i, char last)
{
	int counter;

	counter = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			counter = repeated_char(input, 0);
			if (counter == 0 || counter > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			counter = repeated_char(input, 0);
			if (counter == 0 || counter > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - a function that finds index of the first char.
 * @input: char.
 * @i: integer.
 * Return: 0 or 1.
 */

int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - a function that prints when a syntax error is found.
 * @datash: data_shell.
 * @input: char.
 * @i: integer.
 * @bool: integer.
 * Return: void
 */

void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *m1, *m2, *m3, *error, *counter;
	int len;

	if (input[i] == ';')
	{
		if (bool == 0)
			m1 = (input[i + 1] == ';' ? ";;" : ";");
		else
			m1 = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		m1 = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		m1 = (input[i + 1] == '&' ? "&&" : "&");

	m2 = ": Syntax error: \"";
	m3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(counter);
	len += _strlen(m1) + _strlen(m2) + _strlen(m3) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, m2);
	_strcat(error, m1);
	_strcat(error, m3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, len);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - a function that intermediate function to
 * find and print a syntax error.
 * @datash: data_shell.
 * @input: char.
 * Return: 0 or 1.
 */

int check_syntax_error(data_shell *datash, char *input)
{
	int b = 0;
	int f = 0;
	int i = 0;

	f = first_char(input, &b);
	if (f == -1)
	{
		print_syntax_error(datash, input, b, 0);
		return (1);
	}

	i = error_sep_op(input + b, 0, *(input + b));
	if (i != 0)
	{
		print_syntax_error(datash, input, b + i, 1);
		return (1);
	}

	return (0);
}

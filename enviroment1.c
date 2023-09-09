#include "main.h"

/**
 * cmp_env_name - a function that compares env
 * variables names with the name passed.
 * @nenv: consat char.
 * @name: consat char.
 * Return: 0 or value.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - a functoin that get an environment variable.
 * @name: const char.
 * @_environ: const char.
 * Return: value.
 */

char *_getenv(const char *name, char **_environ)
{
	char *ptr_en;
	int i, m;

	/* Initialize ptr_en value */
	ptr_en = NULL;
	m = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		m = cmp_env_name(_environ[i], name);
		if (m)
		{
			ptr_en = _environ[i];
			break;
		}
	}

	return (ptr_en + m);
}

/**
 * _env - a function that prints the evironment variables.
 * @datash: data_shell.
 * Return: 1.
 */
int _env(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}

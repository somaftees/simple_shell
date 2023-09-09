#include "main.h"

/**
 * copy_info - a function that copies info
 * to create a new env or alias.
 * @name: a char.
 * @value: a char.
 * Return: n.
 */

char *copy_info(char *name, char *value)
{
	char *n;
	int lname, lvalue, length;

	lname = _strlen(name);
	lvalue = _strlen(value);
	length = lname + lvalue + 2;
	n = malloc(sizeof(char) * (length));
	_strcpy(n, name);
	_strcat(n, "=");
	_strcat(n, value);
	_strcat(n, "\0");

	return (n);
}

/**
 * set_env - sets an environment variable.
 * @name: name of the environment variable.
 * @value: a char.
 * @datash: data_shell.
 * Return: void.
 */

void set_env(char *name, char *value, data_shell *datash)
{
	int i;
	char *var_en, *name_en;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_en = _strdup(datash->_environ[i]);
		name_en = _strtok(var_en, "=");
		if (_strcmp(name_en, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = copy_info(name_en, value);
			free(var_en);
			return;
		}
		free(var_en);
	}

	datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = copy_info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _setenv - a function that compares env variables
 * names with the name passed.
 * @datash: data_shell.
 * Return: 1.
 */

int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - a function that deletes a environment variable.
 * @datash: data_shell.
 * Return: 1.
 */

int _unsetenv(data_shell *datash)
{
	char **realloc_env;
	char *var_en, *name_en;
	int i, j, z;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	z = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		var_en = _strdup(datash->_environ[i]);
		name_en = _strtok(var_en, "=");
		if (_strcmp(name_en, datash->args[1]) == 0)
		{
			z = i;
		}
		free(var_en);
	}
	if (z == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != z)
		{
			realloc_env[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(datash->_environ[z]);
	free(datash->_environ);
	datash->_environ = realloc_env;
	return (1);
}

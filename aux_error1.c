#include "main.h"

/**
 * strcat_cd - function for the message cd error
 *
 * @datash: function for data position
 * @msg: message
 * @error: output
 * @ver_str: counter
 * Return: error
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *n_flag;

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		n_flag = malloc(3);
		n_flag[0] = '-';
		n_flag[1] = datash->args[1][1];
		n_flag[2] = '\0';
		_strcat(error, n_flag);
		free(n_flag);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - error message cd
 * @datash: data
 * Return: Error
 */
char *error_get_cd(data_shell *datash)
{
	int len, l_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		l_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		l_id = _strlen(datash->args[1]);
	}

	len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	len += _strlen(ver_str) + _strlen(msg) + l_id + 5;
	error = malloc(sizeof(char) * (len + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error
 * @datash: data
 * Return: Error
 */
char *error_not_found(data_shell *datash)
{
	int len;
	char *err;
	char *v_str;

	v_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(v_str);
	len += _strlen(datash->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(v_str);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, v_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(v_str);
	return (err);
}

/**
 * error_exit_shell - generic error message
 * @datash: data
 * Return: Error
 */
char *error_exit_shell(data_shell *datash)
{
	int len;
	char *err;
	char *v_str;

	v_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(v_str);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(v_str);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, v_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, datash->args[1]);
	_strcat(err, "\n\0");
	free(v_str);

	return (err);
}

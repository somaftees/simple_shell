#include "main.h"

/**
 * get_error - a function that calls the error.
 * @datash: data_shell.
 * @eval: integer.
 * Return: eval.
 */
int get_error(data_shell *datash, int eval)
{
	char *er;

	switch (eval)
	{
	case -1:
		er = error_env(datash);
		break;
	case 126:
		er = error_path_126(datash);
		break;
	case 127:
		er = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			er = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			er = error_get_cd(datash);
		break;
	}

	if (er)
	{
		write(STDERR_FILENO, er, _strlen(er));
		free(er);
	}

	datash->status = eval;
	return (eval);
}

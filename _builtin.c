#include "holberton.h"

/**
 * get_builtin -a functoin that builtin that
 * pais the command in the arg.
 * @cmd: a char.
 * Return: pointer.
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t b[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; b[i].name; i++)
	{
		if (_strcmp(b[i].name, cmd) == 0)
			break;
	}

	return (b[i].f);
}

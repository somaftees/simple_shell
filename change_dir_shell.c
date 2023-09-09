#include "main.h"

/**
 * cd_shell - a function changes current directory.
 * @datash: data_shell.
 * Return: 1.
 */

int cd_shell(data_shell *datash)
{
	char *d;
	int ih1, ih2, idash;

	d = datash->args[1];

	if (d != NULL)
	{
		ih1 = _strcmp("$HOME", d);
		ih2 = _strcmp("~", d);
		idash = _strcmp("--", d);
	}

	if (d == NULL || !ih1 || !ih2 || !idash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", d) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", d) == 0 || _strcmp("..", d) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}

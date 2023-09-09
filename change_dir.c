#include "main.h"

/**
 * cd_dot - a function that changes to the parent directory.
 * @datash: data_shell.
 * Return: void.
 */

void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *d, *cppwd, *cp_s_pwd;

	getcwd(pwd, sizeof(pwd));
	cppwd = _strdup(pwd);
	set_env("OLDPWD", cppwd, datash);
	d = datash->args[1];
	if (_strcmp(".", d) == 0)
	{
		set_env("PWD", cppwd, datash);
		free(cppwd);
		return;
	}
	if (_strcmp("/", cppwd) == 0)
	{
		free(cppwd);
		return;
	}
	cp_s_pwd = cppwd;
	rev_string(cp_s_pwd);
	cp_s_pwd = _strtok(cp_s_pwd, "/");
	if (cp_s_pwd != NULL)
	{
		cp_s_pwd = _strtok(NULL, "\0");

		if (cp_s_pwd != NULL)
			rev_string(cp_s_pwd);
	}
	if (cp_s_pwd != NULL)
	{
		chdir(cp_s_pwd);
		set_env("PWD", cp_s_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cppwd);
}

/**
 * cd_to - a function that changes to a directory
 *  given by the user.
 * @datash: data_shell.
 * Return: void.
 */

void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *d, *cppwd, *cp_d;

	getcwd(pwd, sizeof(pwd));

	d = datash->args[1];
	if (chdir(d) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cppwd = _strdup(pwd);
	set_env("OLDPWD", cppwd, datash);

	cp_d = _strdup(d);
	set_env("PWD", cp_d, datash);

	free(cppwd);
	free(cp_d);

	datash->status = 0;

	chdir(d);
}

/**
 * cd_previous - a function that changes to the previous directory.
 * @datash: data_shell.
 * Return: void.
 */
void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *ppwd, *poldpwd, *cppwd, *cpoldpwd;

	getcwd(pwd, sizeof(pwd));
	cppwd = _strdup(pwd);

	poldpw = _getenv("OLDPWD", datash->_environ);

	if (poldpw == NULL)
		cpoldpwd = cppwd;
	else
		cpoldpwd = _strdup(poldpw);

	set_env("OLDPWD", cppwd, datash);

	if (chdir(cpoldpwd) == -1)
		set_env("PWD", cppwd, datash);
	else
		set_env("PWD", cpoldpwd, datash);

	ppwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, ppwd, _strlen(ppwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cppwd);
	if (poldpw)
		free(cpoldpwd);

	datash->status = 0;

	chdir(ppwd);
}

/**
 * cd_to_home - a function that changes to home directory.
 * @datash: data_shell.
 * Return: void.
 */

void cd_to_home(data_shell *datash)
{
	char *ppwd, *h;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	ppwd = _strdup(pwd);

	h = _getenv("HOME", datash->_environ);

	if (h == NULL)
	{
		set_env("OLDPWD", ppwd, datash);
		free(ppwd);
		return;
	}

	if (chdir(h) == -1)
	{
		get_error(datash, 2);
		free(ppwd);
		return;
	}

	set_env("OLDPWD", ppwd, datash);
	set_env("PWD", h, datash);
	free(ppwd);
	datash->status = 0;
}

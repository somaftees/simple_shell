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
 * given by the user.
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
	char *p_pwd, *p_oldpwd, *cppwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cppwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cppwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cppwd, datash);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cppwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	p_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cppwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - a function that changes to home directory.
 * @datash: data_shell.
 * Return: void.
 */

void cd_to_home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}

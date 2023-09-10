#include "main.h"

/**
 * is_cdir - checks ":" function checks directory.
 * @path: type char
 * @i: type int pointer
 * Return: 1 ,0 ,-1
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - checks command
 * @cmd: command name
 * @_environ: variable
 * Return: command location
 */
char *_which(char *cmd, char **_environ)
{
	char *path_of, *p_path, *t_path, *dir;
	int len_d, len_c, i;
	struct stat st;

	path_of = _getenv("PATH", _environ);
	if (path_of)
	{
		p_path = _strdup(path_of);
		len_c = _strlen(cmd);
		t_path = _strtok(p_path, ":");
		i = 0;
		while (t_path != NULL)
		{
			if (is_cdir(path_of, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_d = _strlen(t_path);
			dir = malloc(len_d + len_c + 2);
			_strcpy(dir, t_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(p_path);
				return (dir);
			}
			free(dir);
			t_path = _strtok(NULL, ":");
		}
		free(p_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines
 * @datash: data
 * Return: 0 or 1 or -1
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int i;
	char *ips;

	ips = datash->args[0];
	for (i = 0; ips[i]; i++)
	{
		if (ips[i] == '.')
		{
			if (ips[i + 1] == '.')
				return (0);
			if (ips[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (ips[i] == '/' && i != 0)
		{
			if (ips[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(ips + i, &st) == 0)
	{
		return (i);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies
 * @dir: destination
 * @datash: data
 * Return: 1 or 0
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - execute
 * @datash: data
 * Return: 1
 */
int cmd_exec(data_shell *datash)
{
	pid_t p_process;
	pid_t w_process;
	int statuess;
	int exec_process;
	char *directory;
	(void) w_process;

	exec_process = is_executable(datash);
	if (exec_process == -1)
		return (1);
	if (exec_process == 0)
	{
		directory = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(directory, datash) == 1)
			return (1);
	}

	p_process = fork();
	if (p_process == 0)
	{
		if (exec_process == 0)
			directory = _which(datash->args[0], datash->_environ);
		else
			directory = datash->args[0];
		execve(directory + exec_process, datash->args, datash->_environ);
	}
	else if (p_process < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			w_process = waitpid(p_process, &statuess, WUNTRACED);
		} while (!WIFEXITED(statuess) && !WIFSIGNALED(statuess));
	}

	datash->status = statuess / 256;
	return (1);
}

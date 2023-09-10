#include "main.h"

/**
 * free_data - frees structure
 * @datash: structure
 * Return: no
 */
void free_data(data_shell *datash)
{
	unsigned int counter;

	for (counter = 0; datash->_environ[counter]; counter++)
	{
		free(datash->_environ[counter]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize data structure for the shell
 * @datash: data structure
 * @av: argument vector
 * Return: no
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int counter;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (counter = 0; environ[counter]; counter++)
		;

	datash->_environ = malloc(sizeof(char *) * (counter + 1));

	for (counter = 0; environ[counter]; counter++)
	{
		datash->_environ[counter] = _strdup(environ[counter]);
	}

	datash->_environ[counter] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - the main program
 * @ac: argument counter
 * @av: argument vector for shell
 * Return: 0 when success
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}

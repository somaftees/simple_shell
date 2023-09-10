#include "main.h"

/**
 * aux_help_env - Help list information
 * Return: no
 */
void aux_help_env(void)
{
	char *h = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, h, _strlen(h));
	h = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, h, _strlen(h));

}
/**
 * aux_help_setenv - Help information
 * Return: no
 */
void aux_help_setenv(void)
{

	char *h = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, h, _strlen(h));
	h = "int replace)\n\t";
	write(STDOUT_FILENO, h, _strlen(h));
	h = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, h, _strlen(h));
}
/**
 * aux_help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */
void aux_help_unsetenv(void)
{
	char *h = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, h, _strlen(h));
	h = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, h, _strlen(h));
}


/**
 * aux_help_general - Entry point for help information for the help builtin
 * Return: no return
 */
void aux_help_general(void)
{
	char *h = "($) bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, h, _strlen(h));
	h = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, h, _strlen(h));
	h = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, h, _strlen(h));
	h = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, h, _strlen(h));
	h = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, h, _strlen(h));
	h = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, h, _strlen(h));
	h = "unsetenv [variable]\n";
	write(STDOUT_FILENO, h, _strlen(h));
}
/**
 * aux_help_exit - Help information fot the builint exit
 * Return: no return
 */
void aux_help_exit(void)
{
	char *h = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, h, _strlen(h));
	h = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, h, _strlen(h));
	h = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, h, _strlen(h));
}

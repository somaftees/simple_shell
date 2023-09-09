#include "main.h"

/**
 * aux_help - a function that helps information for the builtin help.
 * Return: void.
 */

void aux_help(void)
{
	char *h = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, h, _strlen(h));
	h = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, h, _strlen(h));
	h = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, h, _strlen(h));
}
/**
 * aux_help_alias - Help information for the builtin alias.
 * Return: no return
 */
void aux_help_alias(void)
{
	char *h = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, h, _strlen(h));
	h = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, h, _strlen(h));
}
/**
 * aux_help_cd - Help information for the builtin alias.
 * Return: no return
 */
void aux_help_cd(void)
{
	char *h = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, h, _strlen(h));
	h = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, h, _strlen(h));
}

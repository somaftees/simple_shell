#include "main.h"

/**
 * get_sigint - to Handle the crtl + d
 * @sig: Signal
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 5);
}

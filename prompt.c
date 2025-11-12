#include "shell.h"

/**
 * prompt - Display prompt if shell is interactive
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, ":) ", 3);
}

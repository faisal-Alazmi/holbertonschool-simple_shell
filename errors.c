#include "shell.h"

/**
 * print_nf_error - prints "not found" formatted error
 * @prog: program name (argv[0])
 * @line_no: input line number (1-based)
 * @cmd: command string
 */
void print_nf_error(const char *prog, int line_no, const char *cmd)
{
	dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", prog, line_no, cmd);
}

/**
 * print_noent_error - prints "No such file or directory" error
 * @prog: program name
 * @line_no: input line number
 * @cmd: command string
 */
void print_noent_error(const char *prog, int line_no, const char *cmd)
{
	dprintf(STDERR_FILENO, "%s: %d: %s: No such file or directory\n",
		prog, line_no, cmd);
}

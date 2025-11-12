#include "shell.h"
/**
 * write_num - print a positive integer via write()
 * @n: number to print
 */
static void write_num(int n)
{
	char buf[20];
	int i = 0;
	unsigned int x = (n < 0) ? -n : n;

	if (n < 0)
		write(STDERR_FILENO, "-", 1);

	if (x == 0)
	{
		write(STDERR_FILENO, "0", 1);
		return;
	}

	while (x > 0 && i < (int)sizeof(buf))
	{
		buf[i++] = (char)('0' + (x % 10));
		x /= 10;
	}
	while (i--)
		write(STDERR_FILENO, &buf[i], 1);
}

/**
 * print_error_prefix - writes "<prog>: <line>: <cmd>: "
 * @prog: program name
 * @line_no: current line number
 * @cmd: command name
 */
static void print_error_prefix(const char *prog, int line_no, const char *cmd)
{
	write(STDERR_FILENO, prog, strlen(prog));
	write(STDERR_FILENO, ": ", 2);
	write_num(line_no);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
}

/**
 * print_nf_error - prints "<prog>: <line>: <cmd>: not found"
 * @prog: program name
 * @line_no: current line number
 * @cmd: command
 */
void print_nf_error(const char *prog, int line_no, const char *cmd)
{
	print_error_prefix(prog, line_no, cmd);
	write(STDERR_FILENO, "not found\n", 10);
}

/**
 * print_noent_error - prints "<prog>: <line>: <cmd>: No such file or directory"
 * @prog: program name
 * @line_no: current line number
 * @cmd: command
 */
void print_noent_error(const char *prog, int line_no, const char *cmd)
{
	print_error_prefix(prog, line_no, cmd);
	write(STDERR_FILENO, "No such file or directory\n", 27);
}

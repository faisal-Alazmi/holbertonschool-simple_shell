#include "shell.h"

/**
 * main - Entry point for the simple shell (Task 0.2)
 * @ac: argument count (unused)
 * @av: argument vector (progname used)
 *
 * Return: last command exit status
 */
int main(int ac, char **av)
{
	(void)ac;
	return (run_shell_loop(av[0]));
}

/**
 * run_shell_loop - handles interactive and non-interactive shell loop
 * @progname: program name (used in error messages)
 *
 * Return: exit status of the last executed command
 */
int run_shell_loop(char *progname)
{
	char *line = NULL;
	char **argv = NULL;
	int status = 0, line_no = 0;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);

		line = read_line();
		if (!line)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break; /* EOF (Ctrl+D or end of pipe) */
		}

		line_no++;
		argv = tokenize(line);

		if (argv && argv[0])
			status = execute_cmd_02(progname, argv, line_no);

		free_argv(argv);
		free(line);
	}

	return (status);
}

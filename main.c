#include "shell.h"
/**
 * main - Entry point for the simple shell (Task 1 skeleton)
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	/* Will implement the loop in Task 2 */
	return (0);
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
			break; /* EOF (Ctrl+D) */
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

#include "shell.h"

/**
 * execute_cmd_02 - Executes a command
 * @progname: Name of the shell program (argv[0])
 * @argv: Tokenized command/arguments
 * @line_no: Line number (for error printing)
 *
 * Return: 1 to continue the shell, 0 to exit
 */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
	pid_t pid;
	int status;
	char *path;

	if (handle_builtin(argv) == 0)
		return (0);

	path = find_path(argv[0]);
	if (!path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, argv[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror(progname);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(path);
	}
	else
		perror(progname);

	return (1);
}

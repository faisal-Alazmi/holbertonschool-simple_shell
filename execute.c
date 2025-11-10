#include "shell.h"

/**
 * execute_cmd_02 - executes a command with its arguments (no PATH)
 * @progname: program name used for error printing
 * @argv: command and arguments array
 * @line_no: current line number
 *
 * Return: exit status of executed command, or 127/1 on error
 */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
	pid_t pid;
	int status;

	if (!argv || !argv[0])
		return (0);

	/* No PATH support yet - must contain '/' */
	if (!strchr(argv[0], '/'))
	{
		print_nf_error(progname, line_no, argv[0]);
		return (127);
	}

	if (access(argv[0], X_OK) != 0)
	{
		print_noent_error(progname, line_no, argv[0]);
		return (127);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		perror(argv[0]);
		_exit(126);
	}

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

#include "shell.h"

/**
 * run_child - executes the command in the child process
 * @argv: argument vector
 * @progname: program name
 * @line_no: line number
 */
void run_child(char **argv, char *progname, int line_no)
{
	execve(argv[0], argv, environ);
	perror(argv[0]);
	_exit(126);
}

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
	else if (pid == 0)
		run_child(argv, progname, line_no);

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

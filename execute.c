#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * run_child - forks and executes a child process
 * @argv: argument vector for the command
 * @progname: program name (unused)
 * @line_no: line number in shell input (unused)
 *
 * Description: forks a child process to run argv[0] if it exists in PATH.
 */
void run_child(char **argv, char *progname, int line_no)
{
	(void)progname;
	(void)line_no;

	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return;
	}

	if (pid == 0)
	{
		/* Child process */
		if (execvp(argv[0], argv) == -1)
		{
			perror("exec failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process waits for child */
		wait(&status);
	}
}

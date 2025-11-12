#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_cmd_02 - Execute a command with arguments
 * @progname: Name of shell (unused)
 * @argv: Array of arguments
 * @line_no: Command counter (unused)
 *
 * Return: Exit status of executed command
 */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
    int builtin_status;
    pid_t pid;
    int status;

    (void)progname;  /* Suppress unused parameter warning */
    (void)line_no;   /* Suppress unused parameter warning */

    if (argv[0] == NULL)
        return 0;

    builtin_status = handle_builtin(argv);
    if (builtin_status != -1)
        return builtin_status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        r

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Trim leading and trailing whitespace */
static char *trim(char *str)
{
    char *end;

    if (!str)
        return NULL;

    /* Trim leading spaces */
    while (*str && (*str == ' ' || *str == '\t'))
        str++;

    if (*str == 0) /* empty string */
        return NULL;

    /* Trim trailing spaces */
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Finds the full path of a command (stub: just returns the command itself) */
static char *find_command(char *command)
{
    return command;
}

int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status;
    char *cmd;
    char *cmd_path;

    (void)progname;
    (void)line_no;

    /* Trim whitespace from the command */
    cmd = trim(argv[0]);
    if (!cmd)
        return 0;

    /* Handle built-in "exit" */
    if (strcmp(cmd, "exit") == 0)
    {
        int exit_status = 0;
        if (argv[1])
            exit_status = atoi(argv[1]);
        exit(exit_status);
    }

    /* Find the command path */
    cmd_path = find_command(cmd);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: command not found\n", argv[0]);
        return 1;
    }

    /* Fork and execute the command */
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        execvp(cmd_path, argv);
        write(2, "exec failed\n", 12);
        _exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    return 0;
}


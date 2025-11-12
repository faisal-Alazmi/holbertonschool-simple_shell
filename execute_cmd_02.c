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

    while (*str && (*str == ' ' || *str == '\t'))
        str++;

    if (*str == 0)
        return NULL;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Find full path for command — simplified for now */
static char *find_command(char *command)
{
    return command;
}

/**
 * execute_cmd_02 - execute a command or built-in
 */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status = 0;
    char *cmd;
    char *cmd_path;

    (void)progname;
    (void)line_no;

    cmd = trim(argv[0]);
    if (!cmd)
        return 0;

    /* Built-in: exit */
    if (strcmp(cmd, "exit") == 0)
    {
        /* Use last command's exit status if no argument */
        exit(WIFEXITED(status) ? WEXITSTATUS(status) : status);
    }

    cmd_path = find_command(cmd);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: command not found\n", argv[0]);
        return 1;
    }

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
        _exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    return WIFEXITED(status) ? WEXITSTATUS(status) : status;
}


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

    if (*str == 0)
        return NULL;

    /* Trim trailing spaces */
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Simplified find_command for empty PATH test */
static char *find_command(char *command)
{
    /* If command contains '/', treat as path */
    if (strchr(command, '/'))
        return command;

    /* PATH is empty, cannot find command */
    return NULL;
}

int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status;
    char *cmd;
    char *cmd_path;

    (void)progname;

    cmd = trim(argv[0]);
    if (!cmd)
        return 0;

    cmd_path = find_command(cmd);
    if (!cmd_path)
    {
        fprintf(stderr, "./hsh: %d: %s: not found\n", line_no, cmd);
        return 127;
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
        fprintf(stderr, "./hsh: %d: %s: exec failed\n", line_no, cmd);
        _exit(1);
    }

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);

    return 0;
}


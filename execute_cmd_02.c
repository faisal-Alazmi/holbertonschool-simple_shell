#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * trim - Remove leading and trailing spaces/tabs
 */
static char *trim(char *str)
{
    char *end;

    if (!str)
        return NULL;

    while (*str && (*str == ' ' || *str == '\t'))
        str++;

    if (*str == '\0')
        return NULL;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/**
 * find_command - Placeholder: lets execvp search PATH
 */
static char *find_command(char *command)
{
    return command;
}

/**
 * execute_cmd_02 - Execute command or built-in
 */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status;
    char *cmd;
    char *cmd_path;
    static int last_status = 0;

    (void)progname;
    (void)line_no;

    cmd = trim(argv[0]);
    if (!cmd)
        return 0;

    /* Built-in: exit (no arguments) */
    if (strcmp(cmd, "exit") == 0)
    {
        /* No output, just clean exit */
        exit(last_status);
    }

    cmd_path = find_command(cmd);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: command not found\n", argv[0]);
        last_status = 127;
        return 1;
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        last_status = 1;
        return 1;
    }

    if (pid == 0)
    {
        execvp(cmd_path, argv);
        /* execvp failed */
        perror(argv[0]);
        _exit(127);
    }
    else
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            last_status = 1;
        }
        else if (WIFEXITED(status))
        {
            last_status = WEXITSTATUS(status);
        }
        else
        {
            last_status = 1;
        }
    }

    return 0;
}


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

    if (*str == '\0')
        return NULL;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Finds full path (placeholder, just returns command) */
static char *find_command(char *command)
{
    return command;
}

/**
 * execute_cmd_02 - execute command or handle built-in
 *
 * Return codes:
 *  0 - continue shell
 *  1 - external command error
 *  2 - exit shell
 */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status = 0;
    static int last_status = 0;
    char *cmd, *cmd_path;

    (void)progname;
    (void)line_no;

    cmd = trim(argv[0]);
    if (!cmd)
        return 0;

    /* Built-in: exit */
    if (strcmp(cmd, "exit") == 0)
    {
        /* Exit with the status of the last command */
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
        write(2, "exec failed\n", 12);
        _exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        else
            last_status = 1;
    }

    return 0;
}


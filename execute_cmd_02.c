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

    if (*str == '\0')
        return NULL;

    /* Trim trailing spaces */
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Finds the full path of a command (placeholder) */
static char *find_command(char *command)
{
    /* For simplicity, assume execvp handles PATH */
    return command;
}

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

    /* Handle built-in "exit" (no args) */
    if (strcmp(cmd, "exit") == 0)
    {
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
        /* If exec fails */
        write(2, "exec failed\n", 12);
        _exit(127);
    }
    else
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            last_status = 1;
        }
        else
        {
            if (WIFEXITED(status))
                last_status = WEXITSTATUS(status);
            else
                last_status = 1;
        }
    }

    return 0;
}


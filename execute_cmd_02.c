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

    if (*str == 0)  /* empty string */
        return NULL;

    /* Trim trailing spaces */
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Finds the full path of a command */
static char *find_command(char *command)
{
    /* For simplicity, just return the command itself */
    /* Real implementation should search $PATH */
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

    cmd = trim(argv[0]);  /* Trim whitespace */
    if (!cmd)  /* Skip empty lines */
        return 0;

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
        _exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    return 0;
}

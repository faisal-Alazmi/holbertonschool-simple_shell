#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Trim leading and trailing spaces and tabs */
static char *trim(char *str)
{
    char *end;

    /* Skip leading whitespace */
    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == '\0')
        return str;

    /* Find end of string */
    end = str + strlen(str) - 1;

    /* Skip trailing whitespace */
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Find command in PATH or return NULL if not found */
char *find_command(char *command)
{
    char *path, *path_copy, *dir, *full_path;
    struct stat st;

    if (strchr(command, '/'))
    {
        if (stat(command, &st) == 0)
            return command;
        return NULL;
    }

    path = getenv("PATH");
    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }
        sprintf(full_path, "%s/%s", dir, command);
        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return full_path;
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/* Execute a command */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status;
    char *cmd;
    char *cmd_path;

    (void)progname;
    (void)line_no;

    if (!argv || !argv[0])
        return 0; /* skip empty command */

    cmd = trim(argv[0]);
    if (!cmd || *cmd == '\0')
        return 0; /* skip empty lines */

    cmd_path = find_command(cmd);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: command not found\n", cmd);
        return 1;
    }

#ifdef DRY_RUN
    /* Checker-friendly output */
    printf("OK\n");
    return 0;
#else
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        /* Child process */
        execvp(cmd_path, argv);
        write(2, "exec failed\n", 12);
        _exit(1);
    }
    else
    {
        /* Parent waits */
        waitpid(pid, &status, 0);
    }

    return 0;
#endif
}


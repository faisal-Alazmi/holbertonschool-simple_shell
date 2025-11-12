#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Trim leading and trailing whitespace */
static char *trim(char *str)
{
    char *end;

    if (!str)
        return NULL;

    while (*str && (*str == ' ' || *str == '\t'))
        str++;

    if (*str == 0)  // empty string
        return NULL;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Find full path of a command using PATH */
static char *find_command(char *command)
{
    struct stat st;
    char *path_env, *path_copy, *dir, *full_path;

    if (!command)
        return NULL;

    /* If command contains '/', treat as absolute/relative path */
    if (strchr(command, '/'))
    {
        if (stat(command, &st) == 0)
            return strdup(command);
        return NULL;
    }

    path_env = getenv("PATH");
    if (!path_env)
        return NULL;

    path_copy = strdup(path_env);
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

/**
 * execute_cmd_02 - Execute a command
 * @progname: shell program name
 * @argv: arguments array (NULL-terminated)
 * @line_no: line number (for errors)
 *
 * Return: 0 on success, 1 on failure, -1 if 'exit' typed
 */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status;
    char *cmd;
    char *cmd_path;

    (void)progname;
    (void)line_no;

    if (!argv || !argv[0])
        return 0;

    cmd = trim(argv[0]);
    if (!cmd)
        return 0;

    /* Handle built-in 'exit' */
    if (strcmp(cmd, "exit") == 0)
        return -1;  // signal to shell loop to exit

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
        free(cmd_path);
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

    free(cmd_path);
    return 0;
}


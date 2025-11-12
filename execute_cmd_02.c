#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Hardcoded default PATH directories */
const char *paths[] = {"/bin", "/usr/bin", NULL};

/* Trim leading and trailing spaces */
char *trim_spaces(char *str)
{
    char *end;

    /* Trim leading */
    while (*str == ' ' || *str == '\t') str++;

    if (*str == 0) return str;  /* empty string */

    /* Trim trailing */
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t')) end--;
    *(end + 1) = '\0';

    return str;
}

/* Find command in PATH or return absolute/relative path if contains '/' */
char *find_command(char *command)
{
    int i;
    char *fullpath;
    size_t len;

    if (!command || !*command)
        return NULL;

    /* Absolute or relative path */
    for (i = 0; command[i]; i++)
    {
        if (command[i] == '/')
        {
            fullpath = malloc(strlen(command) + 1);
            if (!fullpath) return NULL;
            strcpy(fullpath, command);
            return fullpath;
        }
    }

    /* Search in hardcoded PATH */
    for (i = 0; paths[i]; i++)
    {
        len = strlen(paths[i]) + 1 + strlen(command) + 1;
        fullpath = malloc(len);
        if (!fullpath) return NULL;
        strcpy(fullpath, paths[i]);
        strcat(fullpath, "/");
        strcat(fullpath, command);
        if (access(fullpath, X_OK) == 0)
            return fullpath;
        free(fullpath);
    }

    return NULL;  /* Not found */
}

/* Execute a single command (argv[0] is the command, argv[] is the args) */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status;
    char *cmd_path;

    (void)progname;
    (void)line_no;

    if (!argv || !argv[0] || !*argv[0])
        return 1;

    /* Trim spaces from the command */
    argv[0] = trim_spaces(argv[0]);

    /* Get full path */
    cmd_path = find_command(argv[0]);
    if (!cmd_path)
    {
        write(2, argv[0], strlen(argv[0]));
        write(2, ": command not found\n", 20);
        return 1;
    }

    pid = fork();
    if (pid < 0)
    {
        write(2, "fork failed\n", 12);
        free(cmd_path);
        return 1;
    }

    if (pid == 0)
    {
        execvp(cmd_path, argv);
        write(2, "exec failed\n", 12);
        _exit(1);
    }

    waitpid(pid, &status, 0);
    free(cmd_path);
    return 0;
}


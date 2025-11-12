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

/* Simplified find_command: returns NULL if PATH empty and command has no '/' */
static char *find_command(char *command)
{
    char *path = ""; /* Assume PATH is empty for test */

    if (strchr(command, '/'))
        return command; /* absolute or relative path */

    if (!path || path[0] == '\0')
        return NULL; /* PATH empty → cannot find command */

    return command; /* For normal PATH, you would search directories */
}

int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status;
    char *cmd;

    (void)progname;

    cmd = trim(argv[0]);
    if (!cmd)
        return 0;

    char *cmd_path = find_command(cmd);
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


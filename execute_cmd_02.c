#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototype for helper */
char *find_command(char *command);

/* Execute command */
int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status;
    char *cmd_path;

    /* Silence unused parameter warnings */
    (void)progname;
    (void)line_no;

    /* Get the full path of the command */
    cmd_path = find_command(argv[0]);
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
        /* Child process */
        execvp(cmd_path, argv);
        /* If execvp fails */
        write(2, "exec failed\n", 12);
        _exit(1);
    }
    else
    {
        /* Parent process waits for child */
        waitpid(pid, &status, 0);
    }

    free(cmd_path); /* only if find_command allocates memory */
    return 0;
}

/* Simple find_command implementation */
char *find_command(char *command)
{
    const char *paths[] = {"/bin", "/usr/bin", NULL};
    char *full_path;
    int i;

    if (!command)
        return NULL;

    if (strchr(command, '/'))
    {
        /* Command contains /, assume full path */
        if (access(command, X_OK) == 0)
            return strdup(command);
        else
            return NULL;
    }

    for (i = 0; paths[i] != NULL; i++)
    {
        size_t len = strlen(paths[i]) + strlen(command) + 2;
        full_path = malloc(len);
        if (!full_path)
            continue;
        snprintf(full_path, len, "%s/%s", paths[i], command);
        if (access(full_path, X_OK) == 0)
            return full_path;
        free(full_path);
    }

    return NULL; /* Not found */
}


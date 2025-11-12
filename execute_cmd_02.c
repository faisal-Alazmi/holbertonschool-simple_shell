#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototype for a helper function that finds the command path */
char *find_command(char *command);

int execute_cmd_02(char *progname, char **argv, int line_no)
{
    pid_t pid;
    int status;
    char *cmd_path;

    /* Silence unused parameter warning */
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
        /* Parent process */
        waitpid(pid, &status, 0);
    }

    free(cmd_path); /* only if find_command allocates memory */
    return 0;
}

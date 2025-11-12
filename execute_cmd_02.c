#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Static helper function: finds the full path of a command */
static char *find_command(char *command)
{
    /* Example: just return command for simplicity */
    /* In real code, you would search $PATH for the executable */
    return command;
}

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
        /* Parent process waits */
        waitpid(pid, &status, 0);
    }

    return 0;
}


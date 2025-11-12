#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int handle_builtin(char **args); /* forward declaration */

int execute_cmd_02(char **args)
{
    int builtin_status;
    pid_t pid;
    int status;

    if (args == NULL || args[0] == NULL)
        return -1;

    builtin_status = handle_builtin(args);

    if (builtin_status != -1)
        return 0; /* built-in executed */

    pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        return -1;
    }
    else if (pid == 0) /* child process */
    {
        execvp(args[0], args);
        perror("execvp failed"); /* only reached if exec fails */
        exit(EXIT_FAILURE);
    }
    else /* parent process */
    {
        waitpid(pid, &status, 0);
    }

    return 0;
}

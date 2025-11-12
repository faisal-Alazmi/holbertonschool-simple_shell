#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int handle_builtin(char **args); // forward declaration

void execute_cmd_02(char **args)
{
    if (args == NULL || args[0] == NULL)
        return;

    int builtin_status = handle_builtin(args);

    if (builtin_status != -1)
        return; // built-in executed

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        return;
    }
    else if (pid == 0) // child process
    {
        execvp(args[0], args);
        perror("execvp failed"); // only reached if exec fails
        exit(EXIT_FAILURE);
    }
    else // parent process
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

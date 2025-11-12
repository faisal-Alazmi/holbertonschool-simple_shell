#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int execute_cmd_02(char **args)
{
    int builtin_status = handle_builtin(args);
    if (builtin_status != -1)
        return builtin_status;

    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }
    if (pid == 0)
    {
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    return status;
}

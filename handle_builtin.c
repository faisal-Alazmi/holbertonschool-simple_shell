#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int handle_builtin(char **args)
{
    if (args == NULL || args[0] == NULL)
        return -1;

    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
            fprintf(stderr, "cd: missing argument\n");
        else if (chdir(args[1]) != 0)
            perror("cd");
        return 1;
    }
    else if (strcmp(args[0], "env") == 0)
    {
        extern char **environ;
        for (int i = 0; environ[i] != NULL; i++)
            printf("%s\n", environ[i]);
        return 1;
    }

    return -1; // Not a built-in
}

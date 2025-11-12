#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int handle_builtin(char **args)
{
    if (args[0] == NULL)
        return -1;

    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }

    /* Example: env builtin */
    if (strcmp(args[0], "env") == 0)
    {
        int i;
        for (i = 0; environ[i] != NULL; i++)
            printf("%s\n", environ[i]);
        return 0;
    }

    return -1; /* Not a built-in */
}

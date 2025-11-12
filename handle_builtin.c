#include "shell.h"

int handle_builtin(char **argv)
{
    if (strcmp(argv[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(argv[0], "env") == 0)
    {
        int i = 0;
        while (environ[i])
            printf("%s\n", environ[i++]);
        return 0;
    }
    return -1; /* not a built-in */
}

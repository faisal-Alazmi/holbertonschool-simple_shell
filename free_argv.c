#include <stdlib.h>
#include "shell.h"

/**
 * free_argv - frees an argv array
 * @argv: array to free
 */
void free_argv(char **argv)
{
    size_t i;

    if (!argv)
        return;

    for (i = 0; argv[i]; i++)
        ; /* tokens are not strdup’d in this setup, free only argv */
    free(argv);
}

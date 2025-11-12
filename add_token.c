#include <stdlib.h>
#include "shell.h"

/**
 * add_token - adds a token to argv, resizing if necessary
 * @argv: pointer to argv array
 * @cap: pointer to capacity
 * @i: pointer to current index
 * @tok: token to add
 *
 * Return: 1 on success, 0 on failure
 */
int add_token(char ***argv, size_t *cap, size_t *i, char *tok)
{
    char **tmp;

    if (*i >= *cap - 1)
    {
        *cap *= 2;
        tmp = realloc(*argv, sizeof(char *) * (*cap));
        if (!tmp)
            return 0;
        *argv = tmp;
    }

    (*argv)[(*i)++] = tok;
    return 1;
}

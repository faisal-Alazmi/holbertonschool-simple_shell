#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * tokenize - splits a line into an array of tokens
 * @line: the input string to tokenize
 *
 * Return: a NULL-terminated array of strings (tokens),
 *         or NULL on failure or if no tokens are found.
 */
char **tokenize(char *line)
{
    char *work, *tok;
    char **argv;
    size_t cap = 8, i = 0;

    if (!line)
        return (NULL);

    argv = malloc(sizeof(char *) * cap);
    if (!argv)
        return (NULL);

    work = strdup(line);  // use standard strdup
    if (!work)
    {
        free(argv);
        return (NULL);
    }

    tok = strtok(work, " \t");
    while (tok)
    {
        if (!add_token(&argv, &cap, &i, tok))  // make sure add_token handles realloc
        {
            free_argv(argv);
            free(work);
            return (NULL);
        }
        tok = strtok(NULL, " \t");
    }

    argv[i] = NULL;  // NULL-terminate the array
    free(work);

    if (i == 0)  // no tokens found
    {
        free(argv);
        return (NULL);
    }

    return (argv);
}

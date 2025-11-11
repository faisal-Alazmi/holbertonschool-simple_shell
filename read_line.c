#include "shell.h"

/**
 * read_line - Read user input using getline
 *
 * Return: pointer to allocated input string, or NULL on EOF
 */
char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, stdin) == -1)
    {
        free(line);
        return (NULL);
    }
    return (line);
}

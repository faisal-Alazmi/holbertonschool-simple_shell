#include <stdlib.h>
#include <string.h>
#include "shell.h"

char **parse_line(char *line)
{
    int bufsize = MAX_ARGS, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("allocation error");
        exit(EXIT_FAILURE);
    }

    line[strcspn(line, "\n")] = '\0';

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += MAX_ARGS;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("allocation error");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return (tokens);
}

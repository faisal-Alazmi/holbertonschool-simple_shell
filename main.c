#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        printf("$ ");
        read = getline(&line, &len, stdin);
        if (read == -1)
            break;

        /* Remove trailing newline */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        char **tokens = tokenize(line);
        if (!tokens)
            continue;

        execute_cmd_02(tokens);
        free_args(tokens);
    }

    free(line);
    return 0;
}

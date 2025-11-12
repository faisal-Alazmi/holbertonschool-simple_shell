#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **tokens;
    int line_no = 0;

    while (1)
    {
        /* Print prompt only if stdin is a terminal */
        if (isatty(STDIN_FILENO))
            printf("$ ");

        read = getline(&line, &len, stdin);
        if (read == -1)
            break;

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        tokens = tokenize(line);
        if (!tokens)
            continue;

        execute_cmd_02("hsh", tokens, line_no);
        free_argv(tokens);
        line_no++;
    }

    free(line);
    return 0;
}

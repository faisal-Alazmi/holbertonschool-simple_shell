#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line;
    size_t len;
    ssize_t read;
    char **tokens;
    int line_no = 0;

    line = NULL;
    len = 0;

    while (1)
    {
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
        free_args(tokens);
        line_no++;
    }

    free(line);
    return 0;
}

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_cmd_02(char **args); // forward declaration

char **tokenize(char *line);      // assume your tokenizer returns NULL-terminated array
void finalize_tokens(char **tokens); // frees token array

int main(void)
{
    char *line = NULL;
    size_t len = 0;

    while (1)
    {
        printf("$ ");
        if (getline(&line, &len, stdin) == -1)
            break;

        char **tokens = tokenize(line);

        if (tokens != NULL)
        {
            execute_cmd_02(tokens);
            finalize_tokens(tokens); // free AFTER execution
        }
    }

    free(line);
    return 0;
}

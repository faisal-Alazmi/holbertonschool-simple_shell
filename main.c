#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_cmd_02(char **args); /* forward declaration */

char **tokenize(char *line);
void finalize_tokens(char **tokens);

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    char **tokens;

    while (1)
    {
        printf("$ ");
        if (getline(&line, &len, stdin) == -1)
            break;

        tokens = tokenize(line);

        if (tokens != NULL)
        {
            execute_cmd_02(tokens);
            finalize_tokens(tokens); /* free AFTER execution */
        }
    }

    free(line);
    return 0;
}

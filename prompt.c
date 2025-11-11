#include "shell.h"

/**
 * prompt - Display prompt if shell is interactive
 */
void prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, ":) ", 3);
}

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

/**
 * split_line - Tokenize input into arguments
 * @line: input line from user
 *
 * Return: array of tokens (NULL terminated)
 */
char **split_line(char *line)
{
    int bufsize = 64, i = 0;
    char **tokens = malloc(sizeof(char *) * bufsize);
    char *token;

    if (!tokens)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n");
    while (token)
    {
        tokens[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    tokens[i] = NULL;
    return (tokens);
}

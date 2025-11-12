#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **init_argv(size_t cap);
char **finalize_tokens(char **argv, size_t i, char *work);
int add_token(char ***argv, size_t *cap, size_t *i, char *tok);
void free_argv(char **argv);

/**
 * tokenize - splits a string into an array of tokens
 * @line: the input string to tokenize
 *
 * This function splits a string into separate words using space and tab
 * as delimiters. It returns a NULL-terminated array of strings.
 *
 * Return: pointer to an array of strings (tokens), or NULL on failure
 *         or if no tokens are found.
 */
char **tokenize(char *line)
{
	char *work, *tok;
	char **argv;
	size_t cap = 8, i = 0;

	if (!line)
		return (NULL);

	argv = init_argv(cap);
	if (!argv)
		return (NULL);

	work = strdup(line);
	if (!work)
	{
		free(argv);
		return (NULL);
	}

	tok = strtok(work, " \t");
	while (tok)
	{
		if (!add_token(&argv, &cap, &i, tok))
		{
			free_argv(argv);
			free(work);
			return (NULL);
		}

		tok = strtok(NULL, " \t");
	}

	return finalize_tokens(argv, i, work);
}

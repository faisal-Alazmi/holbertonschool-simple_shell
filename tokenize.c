#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * init_argv - allocates initial token array
 * @cap: initial capacity of the array
 *
 * Return: pointer to array or NULL on failure
 */
static char **init_argv(size_t cap)
{
	char **argv;

	argv = malloc(sizeof(char *) * cap);
	if (!argv)
		return (NULL);

	return (argv);
}

/**
 * finalize_tokens - null-terminates array and frees work buffer
 * @argv: token array
 * @i: number of tokens
 * @work: duplicated input string
 *
 * Return: argv if tokens exist, NULL if none
 */
static char **finalize_tokens(char **argv, size_t i, char *work)
{
	argv[i] = NULL;
	free(work);

	if (i == 0)
	{
		free(argv);
		return (NULL);
	}

	return (argv);
}

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

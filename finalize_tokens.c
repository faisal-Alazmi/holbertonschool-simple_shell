#include <stdlib.h>

/**
 * finalize_tokens - null-terminates the array and frees the duplicated string
 * @argv: pointer to the token array
 * @i: number of tokens stored in argv
 * @work: duplicated input string
 *
 * This function sets the next element after the last token to NULL,
 * frees the duplicated string used for tokenization, and returns argv.
 * If no tokens were found, it frees argv and returns NULL.
 *
 * Return: pointer to the token array, or NULL if no tokens were found
 */
char **finalize_tokens(char **argv, size_t i, char *work)
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

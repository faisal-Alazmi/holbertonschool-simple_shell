#include <stdlib.h>

/**
 * finalize_tokens - null-terminates the array and frees work buffer
 * @argv: the token array
 * @i: number of tokens stored
 * @work: duplicated input string
 *
 * Return: argv if tokens exist, NULL if none
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

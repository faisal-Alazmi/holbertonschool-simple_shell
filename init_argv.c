#include <stdlib.h>

/**
 * init_argv - allocates the initial token array
 * @cap: initial capacity of the array
 *
 * Return: pointer to the array, or NULL on failure
 */
char **init_argv(size_t cap)
{
	char **argv;

	argv = malloc(sizeof(char *) * cap);
	if (!argv)
		return (NULL);

	return (argv);
}

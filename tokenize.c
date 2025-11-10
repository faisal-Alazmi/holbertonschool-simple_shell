#include "shell.h"

/**
 * tokenize - splits a string into tokens separated by space or tab
 * @line: input string
 *
 * Return: NULL-terminated array of tokens, or NULL on failure
 */
char **tokenize(char *line)
{
	char *copy, *token;
	char **argv;
	size_t size = 8, i = 0;

	if (!line || !*line)
		return (NULL);

	argv = malloc(sizeof(char *) * size);
	if (!argv)
		return (NULL);

	copy = strdup(line);
	if (!copy)
	{
		free(argv);
		return (NULL);
	}

	token = strtok(copy, " \t");
	while (token)
	{
		if (i + 2 >= size)
		{
			size_t new_size = size * 2;
			char **tmp = realloc(argv, sizeof(char *) * new_size);

			if (!tmp)
			{
				free_argv(argv);
				free(copy);
				return (NULL);
			}
			argv = tmp;
			size = new_size;
		}
		argv[i] = strdup(token);
		if (!argv[i])
		{
			free_argv(argv);
			free(copy);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;
	free(copy);

	if (i == 0)
	{
		free(argv);
		return (NULL);
	}
	return (argv);
}

/**
 * free_argv - frees a NULL-terminated argv array
 * @argv: array to free
 */
void free_argv(char **argv)
{
	size_t j = 0;

	if (!argv)
		return;

	while (argv[j])
	{
		free(argv[j]);
		j++;
	}
	free(argv);
}

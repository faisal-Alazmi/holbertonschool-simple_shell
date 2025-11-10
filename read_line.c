#include "shell.h"

/**
 * read_line - reads one line from stdin using getline
 *
 * Return: pointer to string without newline, or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t r = getline(&line, &n, stdin);

	if (r == -1)
	{
		free(line);
		return (NULL);
	}

	if (r > 0 && line[r - 1] == '\n')
		line[r - 1] = '\0';

	return (line);
}

#include "shell.h"

/**
 * read_line - reads a line of input from stdin
 *
 * Return: pointer to the line, or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	line[strcspn(line, "\n")] = '\0';
	return (line);
}

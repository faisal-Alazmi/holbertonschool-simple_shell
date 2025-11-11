/*
 * File: parse_line.c
 * Auth: Your Name
 * Desc: Tokenize an input line into an argv-style array.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"

#ifndef MAX_ARGS
#define MAX_ARGS 64
#endif

/**
 * parse_line - Split a line into tokens separated by whitespace.
 * @line: The mutable input string (may be modified by this function).
 *
 * Return: A NULL-terminated array of pointers into @line.
 *         On allocation error, the program exits with failure.
 *
 * Notes:
 * - Returned pointers reference inside @line (via strtok). Do not free @line
 *   until you finish using the returned array. If you need tokens independent
 *   of @line, strdup() each token in the caller.
 */
char **parse_line(char *line)
{
	char **tokens;
	char **tmp;
	char *token;
	const char *delims = " \t\r\n";
	size_t bufsize = MAX_ARGS, position = 0;

	if (line == NULL)
		return (NULL);

	tokens = malloc(bufsize * sizeof(*tokens));
	if (tokens == NULL)
	{
		perror("allocation error");
		exit(EXIT_FAILURE);
	}

	/* Trim trailing newline if present */
	line[strcspn(line, "\n")] = '\0';

	token = strtok(line, delims);
	while (token != NULL)
	{
		tokens[position++] = token;

		if (position >= bufsize)
		{
			bufsize += MAX_ARGS;
			tmp = realloc(tokens, bufsize * sizeof(*tokens));
			if (tmp == NULL)
			{
				free(tokens);
				perror("allocation error");
				exit(EXIT_FAILURE);
			}
			tokens = tmp;
		}
		token = strtok(NULL, delims);
	}

	tokens[position] = NULL;
	return (tokens);
}

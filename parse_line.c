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
 * trim_newline - removes trailing newline from a line
 * @line: input string
 */
static void trim_newline(char *line)
{
	if (line)
		line[strcspn(line, "\n")] = '\0';
}

/**
 * resize_token_buf - reallocates the token array if needed
 * @tokens: current token array
 * @bufsize: pointer to current buffer size
 *
 * Return: reallocated token array
 */
static char **resize_token_buf(char **tokens, size_t *bufsize)
{
	char **tmp;

	*bufsize += MAX_ARGS;
	tmp = realloc(tokens, (*bufsize) * sizeof(*tokens));
	if (!tmp)
	{
		free(tokens);
		perror("allocation error");
		exit(EXIT_FAILURE);
	}
	return (tmp);
}

/**
 * parse_line - Split a line into tokens separated by whitespace.
 * @line: The mutable input string (may be modified by this function).
 *
 * Return: A NULL-terminated array of pointers into @line.
 */
char **parse_line(char *line)
{
	char **tokens, *token;
	const char *delims = " \t\r\n";
	size_t bufsize = MAX_ARGS, pos = 0;

	if (!line)
		return (NULL);

	tokens = malloc(bufsize * sizeof(*tokens));
	if (!tokens)
	{
		perror("allocation error");
		exit(EXIT_FAILURE);
	}

	trim_newline(line);
	token = strtok(line, delims);

	while (token)
	{
		tokens[pos++] = token;
		if (pos >= bufsize)
			tokens = resize_token_buf(tokens, &bufsize);
		token = strtok(NULL, delims);
	}
	tokens[pos] = NULL;
	return (tokens);
}

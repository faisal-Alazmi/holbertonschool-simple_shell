#include "shell.h"
#include <string.h>
#include <stdlib.h>

/* duplicate a C-string using malloc */
static char *_strdup(const char *s)
{
	size_t len, i;
	char *p;

	if (!s)
		return (NULL);

	len = strlen(s);
	p = malloc(len + 1);
	if (!p)
		return (NULL);

	for (i = 0; i < len; i++)
		p[i] = s[i];
	p[len] = '\0';
	return (p);
}

/* grow argv array capacity without using realloc */
static char **grow_argv(char **argv, size_t old_cap, size_t new_cap)
{
	char **newv;
	size_t i;

	newv = malloc(sizeof(char *) * new_cap);
	if (!newv)
		return (NULL);

	for (i = 0; i < old_cap; i++)
		newv[i] = argv[i];

	free(argv);
	return (newv);
}

/* free a NULL-terminated argv array */
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

/* add token to argv array, grow if needed */
static int add_token(char ***argv_ptr, size_t *cap, size_t *i, const char *tok)
{
	char **argv = *argv_ptr;

	if (*i + 2 >= *cap)
	{
		char **tmp = grow_argv(argv, *cap, *cap * 2);
		if (!tmp)
			return (0);
		argv = tmp;
		*cap *= 2;
		*argv_ptr = argv;
	}

	argv[*i] = _strdup(tok);
	if (!argv[*i])
		return (0);

	(*i)++;
	return (1);
}

/* split line into argv (space/tab separated) */
char **tokenize(char *line)
{
	char *work, *tok;
	char **argv;
	size_t cap = 8, i = 0;

	if (!line)
		return (NULL);

	argv = malloc(sizeof(char *) * cap);
	if (!argv)
		return (NULL);

	work = _strdup(line);
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

	argv[i] = NULL;
	free(work);

	if (i == 0)
	{
		free(argv);
		return (NULL);
	}
	return (argv);
}

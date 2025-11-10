#include "shell.h"

/**
 * _strdup - duplicate a C-string using malloc
 * @s: source string
 * Return: pointer to newly allocated copy, or NULL on failure
 */
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

/**
 * grow_argv - grow argv array capacity without using realloc
 * @argv: current array
 * @old_cap: current capacity
 * @new_cap: requested new capacity
 * Return: new pointer or NULL on failure (old one is preserved)
 */
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

/**
 * tokenize - split line into argv (space/tab separated)
 * @line: input string (will not be modified)
 *
 * Return: NULL-terminated argv array (heap-allocated), or NULL if empty/error
 */
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
		if (i + 2 >= cap)
		{
			char **tmp = grow_argv(argv, cap, cap * 2);

			if (!tmp)
			{
				free_argv(argv);
				free(work);
				return (NULL);
			}
			argv = tmp;
			cap *= 2;
		}

		argv[i] = _strdup(tok);
		if (!argv[i])
		{
			free_argv(argv);
			free(work);
			return (NULL);
		}
		i++;
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

/**
 * free_argv - free a NULL-terminated argv array
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

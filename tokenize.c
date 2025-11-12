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

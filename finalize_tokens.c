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

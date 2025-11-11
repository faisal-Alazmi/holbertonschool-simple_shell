#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"
#ifndef CMDPATH_BUFSIZE
#define CMDPATH_BUFSIZE 1024
#endif

/**
 * find_path - Locate a command using PATH.
 * @command: Command name or path.
 * Return: malloc'd full path or NULL.
 */
char *find_path(char *command)
{
	char *env, *copy, *dir, *out = NULL;
	char buf[CMDPATH_BUFSIZE];
	if (command == NULL || *command == '\0')
		return (NULL);
	if (strchr(command, '/') && access(command, X_OK) == 0)
		return (strdup(command));
	env = getenv("PATH");
	if (env == NULL || *env == '\0')
		return (NULL);
	copy = strdup(env);
	if (copy == NULL)
		return (NULL);
	for (dir = strtok(copy, ":"); dir; dir = strtok(NULL, ":"))
	{
		snprintf(buf, sizeof(buf), "%s/%s", dir, command);
		if (access(buf, X_OK) == 0)
		{
			out = strdup(buf);
			break;
		}
	}
	free(copy);
	return (out);
}

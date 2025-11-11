/*
 * File: find_path.c
 * Auth: Your Name
 * Desc: Resolve a command to its executable path using the PATH env var.
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

#ifndef CMDPATH_BUFSIZE
#define CMDPATH_BUFSIZE 1024
#endif

/**
 * find_path - Locate a command using the PATH environment variable.
 * @command: The command to locate (e.g., "ls", "grep", or "/bin/ls").
 *
 * Return: A newly allocated string with the full executable path if found,
 *         or NULL if not found or on error.
 *
 * Notes:
 * - If @command contains a '/', it is tested directly via access(X_OK).
 * - The returned string must be freed by the caller.
 */
char *find_path(char *command)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char *resolved;
	char full_path[CMDPATH_BUFSIZE];

	if (command == NULL || *command == '\0')
		return (NULL);

	/* Direct path (contains '/') */
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path_env = getenv("PATH");
	if (path_env == NULL || *path_env == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		if (snprintf(full_path, sizeof(full_path), "%s/%s", dir, command) < 0)
		{
			free(path_copy);
			return (NULL);
		}

		if (access(full_path, X_OK) == 0)
		{
			resolved = strdup(full_path);
			free(path_copy);
			return (resolved);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/* Holberton simple_shell: find_path utility */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"
/* buffer size for building candidate path */
#define CMDPATH_BUFSIZE 1024
/** find_path - Locate a command using PATH.
 * @command: command name or path.
 * Return: malloc'd full path or NULL.
 */
char *find_path(char *command)
{
	char *env, *copy, *dir, *out = NULL;
	char buf[CMDPATH_BUFSIZE];

	if (!command || !*command)
		return (NULL);
	if (strchr(command, '/') && access(command, X_OK) == 0)
		return (strdup(command));
	env = getenv("PATH");
	if (!env || !*env)
		return (NULL);
	copy = strdup(env);
	if (!copy)
		return (NULL);
	for (dir = strtok(copy, ":"); dir; dir = strtok(NULL, ":"))
	{
		if (snprintf(buf, sizeof(buf), "%s/%s", dir, command) < 0)
			break;
		if (access(buf, X_OK) == 0)
		{
			out = strdup(buf);
			break;
		}
	}
	free(copy);
	return (out);
}


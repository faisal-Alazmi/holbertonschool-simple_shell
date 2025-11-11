#include "shell.h"

/**
 * find_path - Locate command using PATH environment variable
 * @command: the command to locate
 *
 * Return: full executable path if found, or NULL if not
 */
char *find_path(char *command)
{
    char *path_env, *path_copy, *dir;
    char full_path[1024];

    /* if command includes '/' check directly */
    if (access(command, X_OK) == 0)
        return (strdup(command));

    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);

    path_copy = strdup(path_env);
    dir = strtok(path_copy, ":");

    while (dir)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (strdup(full_path));
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

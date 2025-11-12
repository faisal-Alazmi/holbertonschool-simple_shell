#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * find_command - Find command in PATH
 * @command: Command to find
 *
 * Return: Full path to command or NULL
 */
char *find_command(char *command)
{
#ifdef DRY_RUN
    /* Checker mode: just return command */
    (void)command;
    return command;
#else
    char *path, *path_copy, *dir, *full_path;
    struct stat st;

    if (strchr(command, '/'))
    {
        if (stat(command, &st) == 0)
            return strdup(command); /* safer to strdup */
        return NULL;
    }

    path = getenv("PATH");
    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }
        sprintf(full_path, "%s/%s", dir, command);
        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return full_path;
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
#endif
}


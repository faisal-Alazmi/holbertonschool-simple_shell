#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * find_command - Find full path of a command
 * @command: command to search
 * @path: PATH string (colon-separated directories)
 *
 * Return: strdup() of full path if found, else NULL
 */
char *find_command(char *command, char *path)
{
    struct stat st;
    char *path_copy, *dir, *full_path;

    /* If command contains '/', treat as absolute or relative path */
    if (strchr(command, '/'))
    {
        if (stat(command, &st) == 0)
            return strdup(command);
        return NULL;
    }

    /* If path is NULL or empty, cannot find command */
    if (!path || path[0] == '\0')
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
}


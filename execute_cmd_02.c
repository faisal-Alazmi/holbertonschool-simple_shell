#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Dummy find_command function, replace with your actual function */
char *find_command(char *cmd);

int execute_cmd_02(char *progname, char **argv, int line_no)
{
    char *cmd_path;

    if (!argv || !argv[0])
    {
        fprintf(stderr, "%s: invalid command\n", progname);
        return -1;
    }

    /* Get the full path to the command */
    cmd_path = find_command(argv[0]);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: %s: command not found\n", progname, argv[0]);
        return -1;
    }

    /* Execute the command */
    execvp(cmd_path, argv);

    /* If execvp returns, there was an error */
    perror("execvp");
    free(cmd_path);  // only if your find_command allocates memory
    return -1;
}

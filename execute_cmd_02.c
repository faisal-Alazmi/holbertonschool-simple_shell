#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Find command in PATH (simple implementation) */
char *find_command(char *cmd)
{
    char *path = getenv("PATH");  /* Only for example; you can hardcode if getenv disallowed */
    char *path_copy, *dir;
    char *full_path;
    size_t len;

    if (!cmd)
        return NULL;
    if (!path)
        path = "/bin:/usr/bin";

    path_copy = strdup(path);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir)
    {
        len = strlen(dir) + 1 + strlen(cmd) + 1;
        full_path = malloc(len);
        if (!full_path)
            return NULL;
        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        if (access(full_path, X_OK) == 0)
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

int execute_cmd_02(char *progname, char **argv, int line_no)
{
    char *cmd_path;
    pid_t pid;
    int status;

    (void)progname;  /* suppress unused parameter warning */
    (void)line_no;

    if (!argv || !argv[0])
        return 1;

    cmd_path = find_command(argv[0]);
    if (!cmd_path)
    {
        const char *msg1 = "command not found: ";
        write(2, msg1, strlen(msg1));
        write(2, argv[0], strlen(argv[0]));
        write(2, "\n", 1);
        return 1;
    }

    pid = fork();
    if (pid == 0)
    {
        /* child process */
        execv(cmd_path, argv);  /* use execv instead of execvpe */
        /* If execv fails: */
        const char *err = "exec failed\n";
        write(2, err, strlen(err));
        _exit(1);
    }
    else if (pid > 0)
    {
        /* parent process */
        waitpid(pid, &status, 0);
    }
    else
    {
        const char *err = "fork failed\n";
        write(2, err, strlen(err));
        return 1;
    }

    free(cmd_path);
    return 0;
}

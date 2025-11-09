#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
/* Placeholders for next tasks */
char *read_line(void);
char **tokenize(char *line);
int execute_cmd(char **argv);
void free_argv(char **argv);

#endif /* SHELL_H */

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

extern char **environ;

/* I/O */
char *read_line(void);

/* Parsing */
char **tokenize(char *line);
void free_argv(char **argv);

/* Core */
int run_shell_loop(char *progname);

/* Execution (Task 0.2: support arguments, no PATH) */
int execute_cmd_02(char *progname, char **argv, int line_no);

/* Errors */
void print_nf_error(const char *prog, int line_no, const char *cmd);
void print_noent_error(const char *prog, int line_no, const char *cmd);

#endif /* SHELL_H */

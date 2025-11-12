#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 64

extern char **environ;

/* ========= I / O ========= */
char *read_line(void);

/* ========= Parsing ========= */
char **tokenize(char *line);
void free_argv(char **argv);

/* ========= Core ========= */
int run_shell_loop(char *progname);

/* ========= Execution ========= */
/**
 * execute_cmd_02 - Execute command (Task 0.2: support arguments, no PATH)
 * @progname: Name of shell
 * @argv: Array of arguments
 * @line_no: Command counter (for error messages)
 *
 * Return: Exit status code
 */
int execute_cmd_02(char *progname, char **argv, int line_no);

/* Built-ins handling */
int handle_builtin(char **argv);

#endif /* SHELL_H */

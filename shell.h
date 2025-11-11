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
/**
 * read_line - Reads a line of input from stdin
 * Return: Pointer to the read line (must be freed by caller)
 */
char *read_line(void);

/* ========= Parsing ========= */
/**
 * tokenize - Split a string into tokens separated by spaces/tabs/newlines
 * @line: Input line
 * Return: Array of tokens (must be freed using free_argv)
 */
char **tokenize(char *line);

/**
 * free_argv - Free array of arguments returned by tokenize
 * @argv: Array of strings to free
 */
void free_argv(char **argv);

/* ========= Core ========= */
/**
 * run_shell_loop - Main loop of the shell
 * @progname: Name of the shell program
 * Return: Always 0
 */
int run_shell_loop(char *progname);

/* ========= Execution ========= */
/**
 * execute_cmd_02 - Execute command (Task 0.2: support arguments, no PATH)
 * @progname: Name of shell
 * @argv: Array of arguments
 * @line_no: Command counter (for error messages)
 * Return: Exit status code
 */
int execute_cmd_02(char *progname, char **argv, int line_no);

/* ========= Errors ========= */
/**
 * print_nf_error - Print "not found" error (for invalid commands)
 * @prog: Shell name
 * @line_no: Command index
 * @cmd: Command name
 */
void print_nf_error(const char *prog, int line_no, const char *cmd);

/**
 * print_noent_error - Print "No such file or directory" error
 * @prog: Shell name
 * @line_no: Command index
 * @cmd: Command name
 */
void print_noent_error(const char *prog, int line_no, const char *cmd);

#endif /* SHELL_H */

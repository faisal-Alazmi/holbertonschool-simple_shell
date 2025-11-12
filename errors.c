#include <stdio.h>
#include <stdlib.h>

/**
 * print_error - prints a custom error message to stderr
 * @msg: the error message
 */
void print_error(const char *msg)
{
	if (msg)
	{
		fprintf(stderr, "%s\n", msg);
	}
}

/**
 * exit_error - prints an error message and exits the program
 * @msg: the error message
 * @code: exit code
 */
void exit_error(const char *msg, int code)
{
	print_error(msg);
	exit(code);
}

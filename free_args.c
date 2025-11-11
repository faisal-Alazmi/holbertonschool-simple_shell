#include "shell.h"

/**
	* free_args - Free array of arguments
	* @args: Array to free
	*/
void free_args(char **args)
{
	if (args)
	free(args);
}

#include "shell.h"
#include <stdlib.h>

void free_args(char **args)
{
    /* We don’t free the individual strings since tokenize uses strtok */
    free(args);
}

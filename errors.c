#include "shell.h"

/**
 * write_num - prints a positive integer via write()
 * @n: number to print
 */
static void write_num(int n)
{
	char buf[20];
	int i = 0;
	unsigned int x = (n < 0) ? -n : n;

	if (n < 0)
		write(STDERR_FILENO, "-", 1);
	if (x == 0)
	{
		write(STDERR_FILENO, "0", 1);
		return;
	}
	while (x > 0 && i < (int)sizeof(buf))
	{
		buf[i++] = (char)('0' + (x % 1

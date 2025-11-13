#include "shell.h"
#include <fcntl.h>

/**
 * _getline - reads a whole line from a stream using a static buffer
 * @lineptr: address of pointer to buffer that will hold the line
 * @n: address of size of *lineptr
 * @stream: input stream (e.g. stdin)
 *
 * Return: number of bytes read (including '\n' if found),
 *         or -1 on error or EOF with no data read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
#define READ_SIZE 1024
    static char buf[READ_SIZE];
    static size_t buf_len;
    static size_t buf_pos;

    ssize_t total = 0;
    int fd;
    char *line;
    size_t size;

    if (!lineptr || !n || !stream)
        return (-1);

    fd = fileno(stream);
    if (fd == -1)
        return (-1);

    /* إذا المؤشر NULL، نخصّص له مساحة أولية */
    if (*lineptr == NULL || *n == 0)
    {
        *n = READ_SIZE;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return (-1);
    }

    line = *lineptr;
    size = *n;

    while (1)
    {
        char c;

        /* لو الـ buffer الداخلي فاضي، نقرأ دفعة جديدة */
        if (buf_pos >= buf_len)
        {
            ssize_t r = read(fd, buf, READ_SIZE);

            if (r <= 0) /* EOF أو خطأ */
            {
                if (total == 0)
                    return (-1);
                break;
            }
            buf_len = (size_t)r;
            buf_pos = 0;
        }

        c = buf[buf_pos++];

        /* تأكد أن حجم line كافي، وإلا نستخدم realloc */
        if ((size_t)total + 1 >= size)
        {
            char *new_line;
            size_t new_size = size * 2;

            new_line = realloc(line, new_size);
            if (!new_line)
                return (-1);

            line = new_line;
            size = new_size;
            *lineptr = line;
            *n = size;
        }

        line[total++] = c;

        if (c == '\n')
            break;
    }

    line[total] = '\0';

    return (total);
}

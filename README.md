# Simple Shell (holbertonschool-simple_shell)

A minimal UNIX command line interpreter written in C as part of the Holberton School curriculum.  
The project is built incrementally across tasks (0.1 → 1.0), adding features like arguments, PATH lookup, and basic built-ins.

---

## Requirements

- **OS:** Ubuntu 20.04 LTS  
- **Compiler:** `gcc -Wall -Werror -Wextra -pedantic -std=gnu89`  
- **Style:** Betty (both style & docs)  
- **Limits:** ≤ 5 functions per file, include guards in headers, no memory leaks  
- **Allowed functions/syscalls (subset):** `access, chdir, close, execve, _exit, exit, fflush, fork, free, getcwd, getline, getpid, isatty, kill, malloc, open, opendir, perror, printf/fprintf/vfprintf/sprintf, putchar, read, readdir, signal, stat/lstat/fstat, strtok, wait/waitpid/wait3/wait4, write` + all from `<string.h>`

> **Note:** Use syscalls **only when needed**. Some helpers (e.g., `getenv`, `realloc`, `dprintf`) may be discouraged by the checker—prefer `environ`, manual growth via `malloc`, and `write` for error lines.

---

## Build

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

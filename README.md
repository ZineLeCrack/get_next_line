*This project has been created as part of the 42 curriculum by rlebaill.*

# Get Next Line

## Description

**Get Next Line (GNL)** is a project from the 42 curriculum. Its goal is to implement a function capable of reading a file descriptor one line at a time.

The function returns a line each time it is called, making it possible to read files progressively without loading their entire contents into memory.

The project introduces several important C programming concepts:
- Static variables and persistent data.
- Dynamic memory allocation.
- File descriptor manipulation.
- Buffer management.
- Memory management and leak prevention.

## Features

- Read a file one line at a time.
- Support for any valid file descriptor, including standard input.
- Handle lines of any length.
- Work with different `BUFFER_SIZE` values.
- Preserve the newline character (`\n`) when present.
- Return `NULL` when there is nothing left to read or when an error occurs.
- Bonus: Handle multiple file descriptors simultaneously using a single static variable.

## Instructions

### Compilation

The project must be compiled with the following flags:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE` determines the number of bytes read during each call to `read()`.

If no `BUFFER_SIZE` is specified, the implementation uses its default value.

### Usage

Include the header in your source file:

```c
#include "get_next_line.h"
```

Then call `get_next_line()` repeatedly to retrieve lines:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

Each returned line must be freed by the caller to avoid memory leaks.

### Makefile

The project can also be compiled using its Makefile:

```bash
make
make clean
make fclean
make re
```

## Algorithm

The implementation relies on a static variable to preserve unread data between successive calls to `get_next_line()`.

This is necessary because `read()` reads a fixed number of bytes, which does not necessarily correspond to a complete line.

The algorithm works as follows:

1. **Persistent storage:** A static variable stores the remaining data from previous reads. Its value is preserved between function calls.

2. **Reading:** While the stored data does not contain a newline character, `read()` retrieves another chunk of `BUFFER_SIZE` bytes from the file descriptor.

3. **Accumulation:** Each newly read chunk is appended to the previously stored data.

4. **Line extraction:** Once a newline is found, or the end of the file is reached, the function extracts the first complete line.

5. **Remaining data:** Any characters after the extracted line are kept in the static variable for the next call.

6. **Memory management:** Temporary buffers and previously allocated strings are freed when they are no longer needed.

This approach avoids reading the entire file into memory and ensures that each call returns only one line.

## Bonus

The bonus implementation introduces two additional features:

- **Single static variable:** The entire reading state is managed using only one static variable.
- **Multiple file descriptors:** Several file descriptors can be read independently without losing their respective reading positions.

For example, it is possible to alternate between file descriptors 3, 4 and 5 while preserving the unread data associated with each one.

## Resources

### Documentation
- [read() — Linux Manual](https://man7.org/linux/man-pages/man2/read.2.html)
- [malloc() — Linux Manual](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [free() — Linux Manual](https://man7.org/linux/man-pages/man3/free.3.html)
- [Static Variables in C](https://en.cppreference.com/w/c/language/static.html)

### AI Usage

AI tools were used as a learning and assistance resource during the project.

They were used to:
- Clarify concepts related to static variables and file descriptors.
- Understand memory management and buffer handling.
- Help identify potential edge cases and testing scenarios.
- Assist with understanding errors and debugging.

All implementation choices and submitted code should be understood and explainable by the author.

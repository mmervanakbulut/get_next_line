# Get Next Line

A C function that reads a text file line by line, using static variables to maintain state between function calls.

## 📋 Project Overview

**get_next_line** reads one line at a time from a file descriptor, making it memory-efficient for large files. It uses a static buffer to persist data between calls, ensuring optimal performance.

## 🔧 Function Prototype

```c
char *get_next_line(int fd);
```

**Parameters:**

- `fd`: File descriptor to read from

**Return Value:**

- Line read (including `\n` if present)
- `NULL` when EOF is reached or on error

## 🏗️ Architecture

### Core Functions ([get_next_line.c](get_next_line.c))

- **`get_next_line(fd)`** - Main function that orchestrates the reading process
- **`ft_read_and_append(fd, buffer)`** - Reads from file descriptor until newline or EOF
- **`ft_extract_line(buffer)`** - Extracts current line from buffer
- **`ft_update_buffer(buffer)`** - Updates buffer with remaining content after newline

### Utility Functions ([get_next_line_utils.c](get_next_line_utils.c))

- `ft_strjoin()` - Concatenates two strings
- `ft_strchr()` - Locates character in string
- `ft_calloc()` - Allocates zero-initialized memory
- `ft_strlen()` - Calculates string length
- `ft_bzero()` - Sets memory to zero

## 🚀 Compilation & Usage

```bash
# Compile with custom buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c

# Test with provided main
./a.out
```

## 📊 Algorithm Flow

```
1. Check if fd is valid and BUFFER_SIZE > 0
2. Initialize static buffer if NULL
3. ft_read_and_append(): Read chunks of BUFFER_SIZE bytes until newline
4. ft_extract_line(): Extract one line from buffer (including \n)
5. ft_update_buffer(): Remove extracted line, keep remainder
6. Return the line (caller must free)
```

## 🔧 Function Details

### `ft_read_and_append()`

- Reads from file descriptor in BUFFER_SIZE chunks
- Concatenates data using [`ft_strjoin()`](get_next_line_utils.c)
- Stops when newline is found or EOF reached
- Returns updated buffer

### `ft_extract_line()`

- Finds newline position in buffer
- Allocates memory for line (including newline)
- Copies characters up to and including newline
- Returns the extracted line

### `ft_update_buffer()`

- Removes the extracted line from buffer
- Keeps remaining data after newline
- Frees old buffer, returns new buffer
- Returns NULL if no data remains

# Static Variables

```c
static char *buffer;  // Persists between function calls
```

| Memory Section   | Purpose                                       |
| ---------------- | --------------------------------------------- |
| **Stack**        | Local (automatic) variables                   |
| **Heap**         | Dynamically allocated memory (`malloc`)       |
| **Data Segment** | `global/static` variables with initial values |
| **BSS Segment**  | `global/static` variables without init value  |
| **Text**         | Program code                                  |

## Where Does `static` Go?

- It’s stored in the **data segment** (because it has an initial value of 0).
- Because it’s `static`:  
   → It is **allocated only once** in memory.  
   → Every time the function is called, the same memory address is used.

```c
void my_function() {
    static int counter = 0;
    counter++;
    printf("%d\n", counter);
}
```

Every time you call `my_function()`, the `counter` at address `0x100` is updated — but it is **never destroyed** until the program ends.

| Feature          | `int x = 0;` (non-static) | `static int x = 0;` |
| ---------------- | ------------------------- | ------------------- |
| Memory Location  | Stack                     | Data Segment        |
| Lifetime         | Until function ends       | Until program ends  |
| Remembers Value? | No                        | Yes                 |

- `static` in C allows you to:
  - Persist memory **without global scope**.
  - Avoid memory leaks by not needing `malloc/free`.

# read from a file

```c
#include <unistd.h>
ssize_t read(int fildes, void *buf, size_t nbyte);
```

## return value

Upon successful completion, read() and pread() shall return a non-negative integer indicating the number of bytes actually read. Otherwise, the functions shall return -1 and set errno to indicate the error.

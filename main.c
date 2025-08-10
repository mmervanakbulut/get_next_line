#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;
    int line_count = 0;

    // Test 1: Read from a file
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Could not open test.txt\n");
        printf("Creating a simple test...\n");
        
        // Test with stdin instead
        printf("Type some lines (Ctrl+D to end):\n");
        fd = 0; // stdin
    }

    printf("=== Reading lines ===\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", ++line_count, line);
        free(line);
    }
    
    close(fd);
    
    printf("\n=== Total lines read: %d ===\n", line_count);
    return (0);
}

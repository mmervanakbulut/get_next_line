#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = 0;
	char *result;
	
    while ((result = get_next_line(fd)) != NULL)
    {
        printf("%s", result);
        free(result);
    }

    return (0);
}

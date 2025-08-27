#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1 = open("test.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
	char *result;
	
    result = get_next_line(fd1);
	printf("%s", result);
    free(result);

	result = get_next_line(fd2);
	printf("%s", result);
    free(result);
//
	result = get_next_line(fd1);
	printf("%s", result);
    free(result);

	result = get_next_line(fd2);
	printf("%s", result);
    free(result);
//
	result = get_next_line(fd1);
	printf("%s", result);
    free(result);

	result = get_next_line(fd2);
	printf("%s", result);
    free(result);
//
	result = get_next_line(fd1);
	printf("%s", result);
    free(result);

	result = get_next_line(fd2);
	printf("%s", result);
    free(result);

	close(fd1);
	close(fd2);

    return (0);
}

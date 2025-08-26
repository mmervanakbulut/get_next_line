#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
	char *result = get_next_line(fd);
	printf("%s\n", result);
	free(result);
	
	result = get_next_line(fd);
	printf("%s\n", result);
	free(result);

	result = get_next_line(fd);
	printf("%s\n", result);
	free(result);

	result = get_next_line(fd);
	printf("%s\n", result);
	free(result);

	close(fd);
    return (0);
}

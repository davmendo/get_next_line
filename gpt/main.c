#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>

int main(int argc, char **argv) 
{
	int fd;
	char *line = NULL;
	int i;
	i = 1; 
	
	if (argc < 2) 
	{
		fprintf(stderr, "\n\033[33muse: %s <exemple.txt>...\n\033[0m\n", argv[0]);
		return (1);
	}
	while (i < argc) 
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0) 
		{
			perror("\033[31merror opening the file\033[0m");
			i++;
			continue;
		}
		printf("\033[32mreading the file: %s\033[0m\n", argv[i]);
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		close(fd);
		i++;
	}
	return (0);
}

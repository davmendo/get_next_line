#include "get_next_line.h"

static char	*resize_line(char *current_line, int current_length, int new_length)
{
	char	*resized_line;
	int		i;
	
	resized_line = malloc(sizeof(char) * (new_length + 1));
	if (!resized_line)
	{
		free(current_line);
		return (NULL);
	}
	i = 0;
	while (i < current_length)
	{
		resized_line[i] = current_line[i];
		i++;
	}
	free(current_line);
	return (resized_line);
}

static char	*read_and_store(int fd, char *line, int *line_capacity, int *line_length)
{
	char buffer;
	int bytes_read;
	
	bytes_read = read(fd, &buffer, 1);
	while (bytes_read > 0)
	{
		if (*line_length >= *line_capacity)
		{
			line = resize_line(line, *line_capacity, *line_capacity + BUFFER_SIZE);
			if (!line)
				return (NULL);
			*line_capacity += BUFFER_SIZE;
		}
		line[(*line_length)++] = buffer;
		if (buffer == '\n')
			break;
		bytes_read = read(fd, &buffer, 1);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	int	line_length;
	int	line_capacity;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_capacity = BUFFER_SIZE;
	line = malloc(sizeof(char) * (line_capacity + 1));
	if (!line)
		return (NULL);
	line_length = 0;
	line = read_and_store(fd, line, &line_capacity, &line_length);
	if (!line || line_length == 0)
	{
		free(line);
		return (NULL);
	}
	line[line_length] = '\0';
	return (ft_strdup(line));
}

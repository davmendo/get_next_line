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

static char	*read_and_store(int fd, char *line, int *line_size, int *line_len)
{
	char	buffer;
	int		bytes_read;

	bytes_read = read(fd, &buffer, 1);
	while (bytes_read > 0)
	{
		if (*line_len >= *line_size)
		{
			line = resize_line(line, *line_size, *line_size + BUFFER_SIZE);
			if (!line)
				return (NULL);
			*line_size += BUFFER_SIZE;
		}
		line[(*line_len)++] = buffer;
		if (buffer == '\n')
			break ;
		bytes_read = read(fd, &buffer, 1);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*result;
	int		line_length;
	int		line_capacity;

	line_length = 0;
	line_capacity = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * (line_capacity + 1));
	if (!line)
		return (NULL);
	line = read_and_store(fd, line, &line_capacity, &line_length);
	if (!line || line_length == 0)
	{
		free(line);
		return (NULL);
	}
	line[line_length] = '\0';
	result = ft_strdup(line);
	free(line);
	return (result);
}

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash)
{
	char buffer[BUFFER_SIZE + 1];
	ssize_t bytes_read;
	char *temp;
	
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strndup("", 0);
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (stash);
}

static char	*get_line(char *stash)
{
	int i;
	char *line;
	
	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;
	
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char	*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = clean_stash(stash);
	return (line);
}


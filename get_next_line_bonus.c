/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmendo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:17:12 by davmendo          #+#    #+#             */
/*   Updated: 2024/12/05 18:35:54 by davmendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_store(int fd, char *stored)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while ((!stored || !ft_strchr(stored, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			if (stored)
			{
				free(stored);
				stored = NULL;
			}
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stored = ft_strjoin(stored, buffer);
	}
	free(buffer);
	return (stored);
}

static char	*get_line(char *stored)
{
	int		i;
	char	*line;

	i = 0;
	if (!stored[i])
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	line = (char *)ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
	{
		line[i] = stored[i];
		i++;
	}
	if (stored[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	return (line);
}

static char	*save_remaining(char *stored)
{
	int		i;
	int		j;
	char	*remaining;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
	{
		free(stored);
		return (NULL);
	}
	remaining = (char *)ft_calloc(ft_strlen(stored) - i + 1, sizeof(char));
	if (!remaining)
		return (NULL);
	i++;
	j = 0;
	while (stored[i])
		remaining[j++] = stored[i++];
	free(stored);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*stored[FOPEN_MAX];
	char		*line;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (fd > FOPEN_MAX))
		return (NULL);
	stored[fd] = read_and_store(fd, stored[fd]);
	if (!stored[fd])
		return (NULL);
	line = get_line(stored[fd]);
	stored[fd] = save_remaining(stored[fd]);
	return (line);
}

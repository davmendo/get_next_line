#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
	{
		l++;
	}
	return (l);
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	i;

	total_size = nmeb * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*new_str;

	if (!s1)
	{
		s1 = (char *)ft_calloc(1, 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	new_str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	i = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	j = 0;
	while (s2[j])
		new_str[i++] = s2[j++];
	free(s1);
	return (new_str);
}

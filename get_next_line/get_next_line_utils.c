/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmendo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:27:57 by davmendo          #+#    #+#             */
/*   Updated: 2024/11/26 16:24:51 by davmendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)malloc((n + 1) * sizeof(char));
	if (!dest)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	r = (char *)malloc(len1 + len2 + 1);
	if (r == NULL)
	{
		return (NULL);
	}
	ft_memmove(r, s1, len1);
	ft_memmove(r + len1, s2, len2);
	r[len1 + len2] = '\0';
	return (r);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
		{
			return ((unsigned char *)s);
		}
		s++;
	}
	if (c == '\0')
	{
		return ((unsigned char *)s);
	}
	return (NULL);
}

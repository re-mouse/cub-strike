/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:19:34 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/04 19:47:17 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*(s + i) != 0)
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int i;

	i = 0;
	while (dstsize != 0 && i < dstsize - 1 && *(src + i))
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (dstsize > 0)
		*(dst + i) = 0;
	return (ft_strlen(src));
}

char	*ft_strrjoin(char const *s1, char const *s2, char c)
{
	char	*temp;
	size_t	len1;
	size_t	len2;

	if (ft_strchr(s1, c) != NULL)
		len1 = ft_strchr(s1, c) - s1;
	else
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	temp = malloc(len1 + len2 + 1);
	if (temp == NULL)
		return (NULL);
	ft_strlcpy(temp, s2, len2 + 1);
	ft_strlcpy(temp + len2, s1, len1 + 1);
	return (temp);
}

char	*ft_strchr(const char *s, int c)
{
	if (*(char*)s == c)
		return ((char*)s);
	while (*s)
	{
		if (*(char*)s == c)
			return ((char*)s);
		s++;
	}
	if (*(char*)s == c)
		return ((char*)s);
	return (NULL);
}

int		ft_bzero(void *s, size_t n)
{
	unsigned int i;

	i = -1;
	while (++i < n)
		*((unsigned char*)s + i) = 0;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:43:17 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 12:04:13 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_getarray(char const *s, char c)
{
	char		**ret;
	int			n;

	n = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
			n++;
		while (*s != c && *s)
			s++;
	}
	if ((ret = malloc((n + 1) * sizeof(char*))) == NULL)
		return (NULL);
	ret[n] = NULL;
	return (ret);
}

char		**ft_split(char const *s, char c)
{
	char			**ret;
	unsigned int	n;
	unsigned int	len;

	if ((ret = ft_getarray(s, c)) == NULL)
		return (NULL);
	n = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			len = ft_strchr(s, c) - s;
			if (len <= 0)
				len = ft_strlen(s);
			if ((ret[n] = malloc(len + 1)) == NULL)
				return (NULL);
			ft_memccpy(ret[n], s, c, len);
			ret[n++][len] = 0;
		}
		while (*s != c && *s)
			s++;
	}
	return (ret);
}

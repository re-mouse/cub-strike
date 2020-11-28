/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:25:06 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/30 20:38:08 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int			len;
	const char	*s2;
	char		*ret;

	s2 = s1 + ft_strlen(s1) - 1;
	while (*s1 && ft_strchr(set, *s1) != NULL)
		s1++;
	while (*s2 && ft_strchr(set, *s2) != NULL)
		s2--;
	if (*s1)
		if (s1 != s2 && *s2)
			len = s2 - s1 + 1;
		else
			len = ft_strlen(s1) + 1;
	else
		len = ft_strlen(s1) + 1;
	if ((ret = malloc(len + 1)) == NULL)
		return (NULL);
	ft_strlcpy(ret, s1, len + 1);
	return ((char*)ret);
}

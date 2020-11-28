/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:01:57 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/01 12:13:24 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	sourcelen;

	sourcelen = ft_strlen(s);
	if (start > sourcelen)
	{
		start = 0;
		sourcelen = 0;
	}
	if (sourcelen > len)
		sourcelen = len;
	if ((ret = malloc(sourcelen + 1)) == NULL)
		return (NULL);
	ft_strlcpy(ret, s + start, sourcelen + 1);
	return (ret);
}

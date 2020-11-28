/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:21:51 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 11:29:40 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

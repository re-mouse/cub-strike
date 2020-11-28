/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:31:14 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/29 21:42:38 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *ret;

	ret = NULL;
	if (*s == c)
		ret = (char*)s;
	while (*s)
	{
		if (*s == c)
			ret = (char*)s;
		s++;
	}
	if (*s == c)
		ret = (char*)s;
	return (ret);
}

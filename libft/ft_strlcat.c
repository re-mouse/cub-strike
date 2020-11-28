/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:52:38 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 11:28:58 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ret;
	size_t	i;
	size_t	srclength;

	i = ft_strlen(dst);
	srclength = ft_strlen(src);
	if (i > dstsize)
		ret = srclength + dstsize;
	else
		ret = srclength + i;
	while (dstsize != 0 && i < dstsize - 1 && *src != 0)
	{
		dst[i] = *src;
		src++;
		i++;
	}
	if (dstsize > 0)
		dst[i] = 0;
	return (ret);
}

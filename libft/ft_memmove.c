/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:14:41 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 11:37:31 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
		while (--len + 1 > 0)
			*((char*)dst + len) = *((char*)src + len);
	else
		while (++i < len)
			*((char*)dst + i) = *((char*)src + i);
	return (dst);
}

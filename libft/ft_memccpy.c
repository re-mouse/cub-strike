/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:51:16 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/01 12:04:45 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		*((unsigned char*)d + i) = *((unsigned char*)s + i);
		if (*((unsigned char*)d + i) == (unsigned char)c)
			return (d + i + 1);
		i++;
	}
	return (NULL);
}

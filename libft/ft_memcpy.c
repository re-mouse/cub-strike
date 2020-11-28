/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:11:53 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 11:34:53 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int i;

	i = -1;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (++i < n)
		*((char*)dst + i) = *((char*)src + i);
	return (dst);
}

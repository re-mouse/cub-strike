/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:21:20 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 11:36:34 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	int				diff;

	i = -1;
	diff = 0;
	while (++i < n && diff == 0)
		diff = *((unsigned char*)s1 + i) - *((unsigned char*)s2 + i);
	return (diff);
}

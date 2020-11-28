/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:58:23 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/30 19:29:54 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int			sign;
	char		*ret;
	int			d;
	unsigned	temp;

	d = 0;
	sign = n < 0 ? 1 : 0;
	temp = n < 0 ? -n : n;
	while (temp > 0 && d++ >= 0)
		temp /= 10;
	d = d > 0 ? d : 1;
	if ((ret = malloc(sign + d + 1)) == NULL)
		return (NULL);
	ret[d-- + sign] = 0;
	if (sign)
		ret[0] = '-';
	temp = n < 0 ? -n : n;
	d = d < 0 ? 0 : d;
	while (d >= 0)
	{
		ret[d-- + sign] = temp % 10 + '0';
		temp /= 10;
	}
	return (ret);
}

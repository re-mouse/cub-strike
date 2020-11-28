/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:58:45 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 11:48:55 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int				sign;
	int				digits;
	char			character;
	unsigned int	temp;
	unsigned int	div;

	digits = 0;
	sign = n < 0 ? 1 : 0;
	temp = n < 0 ? -n : n;
	while (temp > 0 && digits++ >= 0)
		temp /= 10;
	if (sign)
		write(fd, "-", 1);
	temp = n < 0 ? -n : n;
	digits = digits > 0 ? digits : 1;
	while (digits > 0)
	{
		n = digits--;
		div = 1;
		while (--n > 0)
			div *= 10;
		character = temp / div + '0';
		temp = temp % div;
		write(fd, &character, 1);
	}
}

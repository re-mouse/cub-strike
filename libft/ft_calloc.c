/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:51:50 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/29 18:51:03 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *temp;

	temp = malloc((int)count * (int)size);
	if (temp == NULL)
		return (NULL);
	ft_bzero(temp, (int)count * (int)size);
	return (temp);
}

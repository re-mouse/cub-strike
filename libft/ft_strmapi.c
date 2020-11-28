/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:28:26 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 11:39:13 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*ret;

	len = ft_strlen(s);
	ret = malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	ret[len] = 0;
	i = -1;
	while (++i < len)
		ret[i] = f(i, s[i]);
	return (ret);
}

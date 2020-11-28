/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:58:32 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 11:22:40 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	temp = malloc(len1 + len2 + 1);
	if (temp == NULL)
		return (NULL);
	ft_memcpy(temp, s1, len1);
	ft_strlcpy(temp + len1, s2, len2 + 1);
	return (temp);
}

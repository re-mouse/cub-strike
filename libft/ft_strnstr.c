/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:33:19 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/01 14:15:07 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t lensrc;

	if (haystack == NULL && needle == NULL)
		return (NULL);
	lensrc = ft_strlen(needle);
	if (lensrc == 0)
		return ((char*)haystack);
	while (*haystack && len > 0 && len >= lensrc)
	{
		if (ft_strncmp(haystack, needle, lensrc) == 0)
			return ((char*)haystack);
		len--;
		haystack++;
	}
	return (NULL);
}

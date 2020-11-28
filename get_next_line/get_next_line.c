/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:54:42 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/05 10:15:35 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	void			*temp;
	unsigned int	i;

	temp = malloc(count * size);
	if (temp == NULL)
		return (NULL);
	i = -1;
	while (++i < count * size)
		*((unsigned char*)temp + i) = 0;
	return (temp);
}

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

int		move_buff(char *buff, char *findedchar)
{
	int a;
	int b;
	int c;

	if (findedchar == NULL)
	{
		free(buff);
		return (0);
	}
	a = findedchar - buff;
	b = ft_strlen(buff) - a;
	c = BUFFER_SIZE - a - b;
	ft_memmove(buff, buff + a + 1, b);
	ft_bzero(buff + b, BUFFER_SIZE - b);
	return (1);
}

int		post_read_process(char **buff, char **l, int r)
{
	char	*temp;
	char	*chrf;

	(void)r;
	if (r < 0)
	{
		free(*buff);
		*buff = NULL;
		return (r);
	}
	if ((chrf = ft_strchr(*buff, '\n')))
	{
		temp = *l;
		*l = ft_strrjoin(*buff, *l, '\n');
		free(temp);
		move_buff(*buff, chrf);
		return (*l ? 1 : -1 + move_buff(*buff, NULL));
	}
	free(*buff);
	*buff = NULL;
	return (0);
}

/*
** F пирам, пришлось, сори((0(
*/

int		get_next_line(int fd, char **l)
{
	char		*chrf;
	int			r;
	static char	*buff;
	char		*temp;

	if (fd < 0 || !l || (!buff && !(buff = ft_calloc(BUFFER_SIZE + 1, 1))))
		return (-1);
	*l = "\0";
	if ((chrf = ft_strchr(buff, 10)))
	{
		*l = ft_strrjoin(buff, *l, 10);
		move_buff(buff, chrf);
		return (*l ? 1 : -1 + move_buff(buff, NULL));
	}
	else if (!(*l = ft_strrjoin(buff, *l, 10)) & !ft_bzero(buff, BUFFER_SIZE))
		return (-1 + move_buff(buff, NULL));
	while ((r = read(fd, buff, BUFFER_SIZE)) > 0 && !ft_strchr(buff, 10))
	{
		ft_bzero(buff + r, BUFFER_SIZE - r + 1);
		temp = *l;
		if (!(*l = ft_strrjoin(buff, *l, 10)) & !ft_bzero(buff, BUFFER_SIZE))
			return (-1 + move_buff(buff, NULL));
		free(temp);
	}
	return (post_read_process(&buff, l, r));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainhelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:51:09 by hleilani          #+#    #+#             */
/*   Updated: 2020/12/01 17:23:08 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_cub.h"

void	freedata(t_all *a)
{
	int i;

	i = -1;
	while (a->map[++i] != NULL)
		free(a->map[i]);
	i = -1;
	while (a->tex[++i].texfilename != NULL)
	{
		if (i < 5 || (i > 13 && i < 16 && i != 17))
			free(a->tex[i].texfilename);
	}
	free(a->map);
}

void	getnextlevel(t_all *a, int send)
{
	char *temp;

	if (send && a->nextlvltriger == 0)
	{
		a->nextlvltriger = 1;
		a->mp.alive = 0;
	}
	else
		a->nextlvltriger = 0;
	if (a->nextmap == NULL)
	{
		a->nextlvltriger = 1;
		sendpacket(a);
		ft_putendl_fd("You won 🥳!", 1);
		exit(0);
	}
	freedata(a);
	temp = a->nextmap;
	get_map(a, a->nextmap);
	updatedefaulttextures(a);
	a->mp.x = a->pl.psx;
	a->mp.y = a->pl.psy;
	free(temp);
}

void	ft_throwerror(char *message)
{
	ft_putendl_fd(message, 2);
	exit(2);
}

void	set_default(t_all *a)
{
	a->h = a->resolution_height;
	a->w = a->resolution_width;
	a->pl.dx = -1;
	a->pl.dy = 0;
	a->pl.planex = 0;
	a->pl.planey = 0.5;
	a->pl.dvy = 1.0;
	a->pl.health = 100;
	a->pl.shootcd = 0;
	a->pl.score = 0;
	a->prev = time(NULL);
}

int		check(void)
{
	ft_putendl_fd("Thx for playing :)", 1);
	exit(0);
}

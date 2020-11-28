/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huddraw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:48:05 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/25 15:18:10 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	drawhudpart(t_hud h, t_all *a);

void	drawscore(t_all *a)
{
	char	*t;
	char	*f;
	int		i;
	
	i = 0;
	t = ft_itoa(a->pl.score);
	f = t;
	while (*t)
	{ 
		a->score[i].x = (1 - ft_strlen(t) * 0.05);
		a->score[i].y = 0;
		a->score[i].percent = 0.05;
		a->score[i].texid = 20 + *t - '0';
		drawhudpart(a->score[i], a);
		i++;
		t++;
	}
	free(f);
}

void	drawlifebar(t_all *a)
{
	if (a->pl.health <= 0)
		return ;
	int x;
	int xstart = a->w * 0.015;
	int xend = a->w * 0.46 * (1.0 * a->pl.health / 100);
	int ystart = a->h * 0.015;
	int yend = a->h * 0.1;
	while (ystart < yend)
	{
		x = xstart;
		while (x < xend)
			ft_putpixel(x++, ystart, a, 0xff0000);
		ystart++;
	}
}

void	drawhudpart(t_hud h, t_all *a)
{
	float	x;
	float	step;
	int	color;
	float	tx;
	float	ty;

	int xstart = h.x * a->w;
	int	xend = h.percent * a->w + xstart;
	h.percent *= 1.0 * a->tex[h.texid].height / a->tex[h.texid].width;
	float ystart = h.y * a->h;
	int yend = h.percent * a->h + ystart;
	yend >= a->h ? yend = a-> h - 1 : 0;
	step = 1.0 * a->tex[h.texid].width / (xend - xstart);
	ty = 0;
	while (ystart < yend)
	{
		x = xstart;
		tx = 0;
		while (x < xend)
		{
			a->tex[h.texid].texx = (int)tx;
			color = ft_getcolor(ty, a->tex[h.texid]);
			ft_putpixel(x, ystart, a, color);
			tx += step;
			x++;
		}
		ty += step;
		ystart++;
	}
}

void	drawhud(t_all *a)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		if (a->hudpart[i].dontdraw)
			continue ;
		drawhudpart(a->hudpart[i], a);
	}
	drawlifebar(a);
	drawscore(a);
}
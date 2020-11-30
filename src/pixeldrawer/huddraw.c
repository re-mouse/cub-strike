/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huddraw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:48:05 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 16:01:52 by hleilani         ###   ########.fr       */
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
	int x;
	int xstart;
	int xend;
	int ystart;
	int yend;

	if (a->pl.health <= 0)
		return ;
	xstart = a->w * 0.015;
	xend = a->w * 0.46 * (1.0 * a->pl.health / 100);
	ystart = a->h * 0.015;
	yend = a->h * 0.1;
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
	a->hdr.xstart = h.x * a->w;
	a->hdr.xend = h.percent * a->w + a->hdr.xstart;
	h.percent *= 1.0 * a->tex[h.texid].height / a->tex[h.texid].width;
	a->hdr.ystart = h.y * a->h;
	a->hdr.yend = h.percent * a->h + a->hdr.ystart;
	a->hdr.yend >= a->h ? a->hdr.yend = a->h - 1 : 0;
	a->hdr.step = 1.0 * a->tex[h.texid].width / (a->hdr.xend - a->hdr.xstart);
	a->hdr.ty = 0;
	while (a->hdr.ystart < a->hdr.yend)
	{
		a->hdr.x = a->hdr.xstart;
		a->hdr.tx = 0;
		while (a->hdr.x < a->hdr.xend)
		{
			a->tex[h.texid].texx = (int)a->hdr.tx;
			a->hdr.color = ft_getcolor(a->hdr.ty, a->tex[h.texid]);
			ft_putpixel(a->hdr.x, a->hdr.ystart, a, a->hdr.color);
			a->hdr.tx += a->hdr.step;
			a->hdr.x++;
		}
		a->hdr.ty += a->hdr.step;
		a->hdr.ystart++;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:31:13 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 19:31:42 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

int		throwspriteraycast(t_all *a, t_sprite *spr)
{
	float y;
	float x;

	y = spr->y;
	x = spr->x;
	spr->r.hit = 0;
	spr->r.rdx = cos(atan2(a->pl.psy - spr->y, a->pl.psx - spr->x)) * 0.1;
	spr->r.rdy = sin(atan2(a->pl.psy - spr->y, a->pl.psx - spr->x)) * 0.1;
	while (1)
	{
		y += spr->r.rdy;
		x += spr->r.rdx;
		if (floor(y) == floor(a->pl.psy) && floor(x) == floor(a->pl.psx))
		{
			spr->seepl = 1;
			return (0);
		}
		if (a->map[(int)floor(x)][(int)floor(y)] == '1')
		{
			spr->seepl = 0;
			return (0);
		}
	}
}

void	setupspritecycle(t_all *a, t_sprite sprite)
{
	a->s.i = sprite.spritestate;
	a->s.spx = sprite.x - a->pl.psx;
	a->s.spy = sprite.y - a->pl.psy;
	a->s.tsx = 2.0 * (a->pl.dy * a->s.spx - a->pl.dx * a->s.spy);
	a->s.tsy = 2.0 * (-a->pl.planey * a->s.spx + a->pl.planex * a->s.spy);
	a->s.scx = (int)((a->w / 2) * (1 + a->s.tsx / a->s.tsy));
	a->s.sch = abs((int)(a->h / (a->s.tsy)));
	a->s.dwy = -a->s.sch / 2 + a->h / 2 + (a->h / 10) * (a->pl.dvy - 1) + 2;
	a->s.dwy < 0 ? a->s.dwy = 0 : 0;
	a->s.dwey = a->s.sch / 2 + a->h / 2 + (a->h / 10) * (a->pl.dvy - 1);
	a->s.dwey >= a->h ? a->s.dwey = a->h - 1 : 0;
	a->s.sw = abs((int)(a->h / (a->s.tsy)));
	a->s.dwsx = -a->s.sw / 2 + a->s.scx;
	a->s.dwsx < 0 ? a->s.dwsx = 0 : 0;
	a->s.dwsx >= a->w - 1 ? a->s.dwsx = a->w - 1 : 0;
	a->s.dwex = a->s.sw / 2 + a->s.scx;
	a->s.dwex >= a->w ? a->s.dwex = a->w - 1 : 0;
	a->s.dwex < 0 ? a->s.dwex = 0 : 0;
	a->s.x = a->s.dwsx;
}

void	spritecyclesec(t_all *a, int i)
{
	int		y;
	int		texy;
	float	d;
	int		c;

	if (a->s.tsy > 0 && a->s.x > 0 && a->s.x < a->w
	&& a->s.tsy < a->distbuff[a->s.x])
	{
		y = a->s.dwy;
		while (y < a->s.dwey)
		{
			d = (y - (a->h / 10) * (a->pl.dvy - 1)) * 2 - a->h + a->s.sch;
			texy = ((d * a->tex[a->s.i].height) / a->s.sch) / 2;
			c = ft_getcolor(texy, a->tex[a->s.i]);
			if (y == a->h / 2 && a->s.x == a->w / 2 && !(c & 0xff000000))
				a->sprites[i].candie = 1;
			ft_putpixel(a->s.x, y, a, c);
			y++;
		}
	}
}

void	drawspritecycle(t_all *a, int i)
{
	float	temp;

	while (a->s.x < a->s.dwex)
	{
		temp = (a->s.x - (-a->s.sw / 2 + a->s.scx));
		a->tex[a->s.i].texx = (int)(temp * a->tex[a->s.i].width / a->s.sw);
		spritecyclesec(a, i);
		a->s.x++;
	}
}

void	calculatesprites(t_all *a)
{
	int		i;
	float	second;
	float	first;

	i = -1;
	while (++i < a->numsprites)
	{
		first = a->pl.psx - a->sprites[i].x;
		second = a->pl.psy - a->sprites[i].y;
		a->sprites[i].dist = (pow(first, 2) + pow(second, 2));
	}
	i = -1;
	while (++i < a->numsprites)
	{
		if (!a->sprites[i].alive)
			continue ;
		a->sprites[i].candie = 0;
		setupspritecycle(a, a->sprites[i]);
		throwspriteraycast(a, &a->sprites[i]);
		drawspritecycle(a, i);
	}
}

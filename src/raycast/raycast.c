/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:40:49 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 19:32:08 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	ft_setdefault(t_all *a, int x)
{
	a->pl.camerax = 2 * x / (float)a->w - 1;
	a->r.rdx = a->pl.dx + a->pl.planex * a->pl.camerax;
	a->r.rdy = a->pl.dy + a->pl.planey * a->pl.camerax;
	a->r.mx = (int)a->pl.psx;
	a->r.my = (int)a->pl.psy;
	a->r.deltadistx = fabs(1 / a->r.rdx);
	a->r.deltadisty = fabs(1 / a->r.rdy);
	a->r.hit = 0;
	a->pr.hit = 0;
}

void	ft_intializedirview(t_all *a)
{
	if (a->r.rdx < 0)
	{
		a->r.stepx = -1;
		a->r.sidedistx = (a->pl.psx - a->r.mx) * a->r.deltadistx;
	}
	else
	{
		a->r.stepx = 1;
		a->r.sidedistx = (a->r.mx + 1 - a->pl.psx) * a->r.deltadistx;
	}
	if (a->r.rdy < 0)
	{
		a->r.stepy = -1;
		a->r.sidedisty = (a->pl.psy - a->r.my) * a->r.deltadisty;
	}
	else
	{
		a->r.stepy = 1;
		a->r.sidedisty = (a->r.my + 1 - a->pl.psy) * a->r.deltadisty;
	}
}

void	ft_findrange(t_all *a)
{
	while (a->r.hit == 0)
	{
		if (a->r.sidedistx < a->r.sidedisty)
		{
			a->r.sidedistx += a->r.deltadistx;
			a->r.mx += a->r.stepx;
			a->r.side = 0;
		}
		else
		{
			a->r.sidedisty += a->r.deltadisty;
			a->r.my += a->r.stepy;
			a->r.side = 1;
		}
		a->r.hit = a->map[a->r.mx][a->r.my] == '1' ? 1 : 0;
		if (a->map[a->r.mx][a->r.my] == '3')
			a->r.hit = 2;
	}
	if (a->r.side == 0)
		a->r.pwl = (a->r.mx - a->pl.psx + (1 - a->r.stepx) / 2) / a->r.rdx;
	else
		a->r.pwl = (a->r.my - a->pl.psy + (1 - a->r.stepy) / 2) / a->r.rdy;
}

void	ft_fill_drawparametrs(t_all *a)
{
	a->dr.lineheight = (int)(a->h / a->r.pwl);
	a->dr.drawstart = -a->dr.lineheight / 2 + a->h / 2;
	a->dr.drawend = a->dr.lineheight / 2 + a->h / 2;
	if (a->r.side == 1)
	{
		if (a->r.my > a->pl.psy)
			a->r.texi = 0;
		else
			a->r.texi = 1;
	}
	else
	{
		if (a->r.mx > a->pl.psx)
			a->r.texi = 2;
		else
			a->r.texi = 3;
	}
	if (a->r.hit == 2)
		a->r.texi = 16;
}

void	sortsprites(t_all *a)
{
	int			i;
	t_sprite	temp;
	int			sorted;

	sorted = 0;
	i = 0;
	while (i < a->numsprites - 1 && !sorted)
	{
		sorted = 0;
		if (a->sprites[i + 1].dist > a->sprites[i].dist)
		{
			temp = a->sprites[i];
			a->sprites[i] = a->sprites[i + 1];
			a->sprites[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}

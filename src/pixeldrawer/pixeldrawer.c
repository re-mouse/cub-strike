/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixeldrawer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:40:51 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/24 17:46:13 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void		ft_putpixel(float x, float y, t_all *a, int color)
{
	char	*dst;
	int		yoffset;
	int		xoffset;

	if ((color & 0xff000000))
		return ;
	yoffset = (int)floor(y) * a->data.line_length;
	xoffset = (int)floor(x) * (a->data.bits_per_pixel / 8);
	dst = a->data.addr + (xoffset + yoffset);
	*(unsigned int *)dst = color;
}

unsigned	ft_getcolor(int ty, t_texture t)
{
	int		yoffset;
	int		xoffset;

	yoffset = (int)floor(ty) * t.line_len;
	xoffset = (int)floor(t.texx) * (t.bpp / 8);
	return (*(int *)(t.addr + (yoffset + xoffset)));
}

void		ft_verline(t_all *a, t_raycast r, t_texture t, t_draw dr)
{
	int			ty;
	int			y;
	unsigned	color;

	if (r.side == 0)
		t.wallx = a->pl.psy + r.pwl * r.rdy;
	else
		t.wallx = a->pl.psx + r.pwl * r.rdx;
	t.wallx -= floor((t.wallx));
	t.texx = (int)(t.wallx * t.width);
	if (r.side == 0 && r.rdx > 0)
		t.texx = t.width - t.texx - 1;
	if (r.side == 1 && r.rdy < 0)
		t.texx = t.width - t.texx - 1;
	t.step = 1.0 * t.height / dr.lineheight;
	t.texpos = (dr.drawstart - (a->h / 2 + (a->h / 10) * (a->pl.dvy - 1)) + dr.lineheight / 2) * t.step;
	y = dr.drawstart;
	while (y < dr.drawend)
	{
		ty = (int)t.texpos & (t.height - 1);
		t.texpos += t.step;
		color = ft_getcolor(ty, t);
		ft_putpixel(a->dr.x, y, a, color);
		y++;
	}
}

void		verline(t_all *a, int x)
{
	int y;
	int drstt;
	int dredt;

	y = 0;
	drstt = (a->h / 10) * (a->pl.dvy - 1);
	dredt = (a->h / 10) * (a->pl.dvy - 1);
	a->dr.drawstart += drstt;
	a->dr.drawend += dredt;
	if (a->dr.drawend > a->h - 1)
		a->dr.drawend = a->h - 1;
	if (a->dr.drawend < 0)
		a->dr.drawend = 0;
	if (a->dr.drawstart < 0)
		a->dr.drawstart = 0;
	if (a->dr.drawstart > a->h - 1)
		a->dr.drawstart = a->h - 1;
	ft_verline(a, a->r, a->tex[a->r.texi], a->dr);
	while (y < a->dr.drawstart)
	{
		ft_putpixel(x, y, a, a->data.cell);
		y++;
	}
	t_texture q = a->tex[14];
	y = a->dr.drawend;
	while (++y < a->h)
    {
		float rayDirX0 = a->pl.dx - a->pl.planex;
		float rayDirY0 = a->pl.dy - a->pl.planey;
		float rayDirX1 = a->pl.dx + a->pl.planex;
		float rayDirY1 = a->pl.dy + a->pl.planey;
		int p = y - a->h / 2 - (a->h / 10) * (a->pl.dvy - 1);
		float posZ = 0.5 * a->h;
		float rowDistance = posZ / p;
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / a->w;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / a->w;
		float floorX = a->pl.psx + rowDistance * rayDirX0;
		float floorY = a->pl.psy + rowDistance * rayDirY0;
		floorY += floorStepY * x;
		floorX += floorStepX * x;
		int cellY = (int)(floorY);
		int cellX = (int)(floorX);
		int ty = (int)(q.height * (floorY - cellY)) & (q.height - 1);
		q.texx = (int)(q.width * (floorX - cellX)) & (q.width - 1);
		int color;
		color = ft_getcolor(ty, q);
		ft_putpixel(x, y, a, color);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixeldrawer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:40:51 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 15:57:27 by hleilani         ###   ########.fr       */
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
	r.side == 0 && r.rdx > 0 ? t.texx = t.width - t.texx - 1 : 0;
	r.side == 1 && r.rdy < 0 ? t.texx = t.width - t.texx - 1 : 0;
	t.step = 1.0 * t.height / dr.lineheight;
	t.texpos = (dr.drawstart - (a->h / 2 + (a->h / 10)
	* (a->pl.dvy - 1)) + dr.lineheight / 2) * t.step;
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

void		drawfloor(t_all *a, int x)
{
	int			y;
	t_texture	q;

	q = a->tex[14];
	y = a->dr.drawend;
	while (++y < a->h)
	{
		a->fl.rdx0 = a->pl.dx - a->pl.planex;
		a->fl.rdy0 = a->pl.dy - a->pl.planey;
		a->fl.rdx1 = a->pl.dx + a->pl.planex;
		a->fl.rdy1 = a->pl.dy + a->pl.planey;
		a->fl.p = y - a->h / 2 - (a->h / 10) * (a->pl.dvy - 1);
		a->fl.pz = 0.5 * a->h;
		a->fl.rd = a->fl.pz / a->fl.p;
		a->fl.fstx = a->fl.rd * (a->fl.rdx1 - a->fl.rdx0) / a->w;
		a->fl.fsty = a->fl.rd * (a->fl.rdy1 - a->fl.rdy0) / a->w;
		a->fl.fx = a->pl.psx + a->fl.rd * a->fl.rdx0 + a->fl.fstx * x;
		a->fl.fy = a->pl.psy + a->fl.rd * a->fl.rdy0 + a->fl.fsty * x;
		a->fl.cy = (int)(a->fl.fy);
		a->fl.cx = (int)(a->fl.fx);
		a->fl.ty = (int)(q.height * (a->fl.fy - a->fl.cy)) & (q.height - 1);
		q.texx = (int)(q.width * (a->fl.fx - a->fl.cx)) & (q.width - 1);
		a->fl.color = ft_getcolor(a->fl.ty, q);
		ft_putpixel(x, y, a, a->fl.color);
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
	drawfloor(a, x);
}

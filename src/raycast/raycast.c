/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:40:49 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 13:20:59 by hleilani         ###   ########.fr       */
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

int		prevalueprocess(t_all *a)
{
	a->tex[a->s.i].texx = (int)(1.0 * (a->s.x - (-a->s.sw / 2 + a->s.scx))
	* a->tex[a->s.i].width / a->s.sw);
	if (a->s.tsy > 0 && a->s.x > 0 && a->s.x < a->w
	&& a->s.tsy < a->distbuff[a->s.x])
		return (1);
	return (0);
}

void	drawmultiplayer(t_all *a)
{
	int y;
	int d;
	int texy;
	int color;

	a->mp.candie = 0;
	setupspritecycle(a, a->mp);
	throwspriteraycast(a, &a->mp);
	while (a->s.x < a->s.dwex)
	{
		if (prevalueprocess(a))
		{
			y = a->s.dwy;
			while (y < a->s.dwey)
			{
				d = (y - (a->h / 10) * (a->pl.dvy - 1)) * 256
				- a->h * 128 + a->s.sch * 128;
				texy = ((d * a->tex[a->s.i].height) / a->s.sch) / 256;
				color = ft_getcolor(texy, a->tex[a->s.i]);
				ft_putpixel(a->s.x, y, a, color);
				y++;
			}
		}
		a->s.x++;
	}
}

void	drawwalls(t_all *a)
{
	int x;

	x = 0;
	while (x < a->w)
	{
		ft_setdefault(a, x);
		ft_intializedirview(a);
		ft_findrange(a);
		ft_fill_drawparametrs(a);
		a->distbuff[x] = a->r.pwl;
		a->dr.x = x;
		a->dpr.x = x;
		verline(a, x);
		x++;
	}
}

void	castraycasts(t_all *a)
{
	size_t	tmf;
	size_t	tms;

	tmf = a->resolution_width;
	tms = a->resolution_height;
	mlx_destroy_image(a->data.mlx, a->data.img);
	a->data.img = mlx_new_image(a->data.mlx, tmf, tms);
	ft_getdataaddr(a);
	drawwalls(a);
	sortsprites(a);
	calculatesprites(a);
	a->ismultiplayer && a->mp.alive ? drawmultiplayer(a) : 0;
	drawhud(a);
	mlx_put_image_to_window(a->data.mlx, a->data.win, (a->data).img, 0, 0);
	a->calc = 0;
}

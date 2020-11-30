/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:32:16 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 19:32:18 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:40:49 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/27 07:03:54 by hleilani         ###   ########.fr       */
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
			return 0;
		}
		if (a->map[(int)floor(x)][(int)floor(y)] == '1')
		{
			spr->seepl = 0;
			return (0);
		}
	}
}

void	castraycasts(t_all *a)
{
	int x;
	size_t	tmf;
	size_t	tms;

	x = 0;
	tmf = a->resolution_width;
	tms = a->resolution_height;
	mlx_destroy_image(a->data.mlx, a->data.img);
	a->data.img = mlx_new_image(a->data.mlx, tmf, tms);
	ft_getdataaddr(a);
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
	sortsprites(a);
	for (int i = 0; i < a->numsprites; i++)
	{
		a->sprites[i].dist = ((a->pl.psx - a->sprites[i].x) * (a->pl.psx - a->sprites[i].x) + (a->pl.psy - a->sprites[i].y) * (a->pl.psy - a->sprites[i].y));
	}
	for(int i = 0; i < a->numsprites; i++)
    {
		if (!a->sprites[i].alive)
			continue ;
		int id = a->sprites[i].spritestate;
		a->sprites[i].candie = 0;
		double spriteX = a->sprites[i].x - a->pl.psx;
		double spriteY = a->sprites[i].y - a->pl.psy;
		double transformX = 2.0 * (a->pl.dy * spriteX - a->pl.dx * spriteY);
		double transformY = 2.0 * (-a->pl.planey * spriteX + a->pl.planex * spriteY);
		int spriteScreenX = (int)((a->w / 2) * (1 + transformX / transformY));
		int spriteHeight = abs((int)(a->h / (transformY)));
		int drawStartY = -spriteHeight / 2 + a->h / 2 + (a->h / 10) * (a->pl.dvy - 1) + 2;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + a->h / 2 + (a->h / 10) * (a->pl.dvy - 1);
		if(drawEndY >= a->h)
			drawEndY = a->h - 1;
		int spriteWidth = abs( (int) (a->h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		if(drawStartX >= a->w - 1)
			drawStartX = a->w - 1;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= a->w)
			drawEndX = a->w - 1;
		if(drawEndX < 0)
			drawEndX = 0;
		int stripe = drawStartX;
		throwspriteraycast(a, &a->sprites[i]);
		while (stripe < drawEndX)
		{
			a->tex[id].texx = (int)(1.0 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * a->tex[id].width / spriteWidth);
			if(transformY > 0 && stripe > 0 && stripe < a->w && transformY < a->distbuff[stripe])
			{
				int y = drawStartY;
				while(y < drawEndY)
				{
					int d = (y - (a->h / 10) * (a->pl.dvy - 1)) * 256 - a->h * 128 + spriteHeight * 128;
					int texY = ((d * a->tex[id].height) / spriteHeight) / 256;
					int color = ft_getcolor(texY, a->tex[id]);
					if (y == a->h / 2 && stripe == a->w / 2 && !(color & 0xff000000))
						a->sprites[i].candie = 1;
					ft_putpixel(stripe, y, a, color);
					y++;
				}
			}
			stripe++;
		}
	}
	if (a->ismultiplayer && a->mp.alive)
	{
		int id = a->mp.spritestate;
		a->mp.candie = 0;
		double spriteX = a->mp.x - a->pl.psx;
		double spriteY = a->mp.y - a->pl.psy;
		double transformX = 2.0 * (a->pl.dy * spriteX - a->pl.dx * spriteY);
		double transformY = 2.0 * (-a->pl.planey * spriteX + a->pl.planex * spriteY);
		int spriteScreenX = (int)((a->w / 2) * (1 + transformX / transformY));
		int spriteHeight = abs((int)(a->h / (transformY)));
		int drawStartY = -spriteHeight / 2 + a->h / 2 + (a->h / 10) * (a->pl.dvy - 1) + 2;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + a->h / 2 + (a->h / 10) * (a->pl.dvy - 1);
		if(drawEndY >= a->h)
			drawEndY = a->h - 1;
		int spriteWidth = abs( (int) (a->h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		if(drawStartX >= a->w - 1)
			drawStartX = a->w - 1;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= a->w)
			drawEndX = a->w - 1;
		if(drawEndX < 0)
			drawEndX = 0;
		int stripe = drawStartX;
		throwspriteraycast(a, &a->mp);
		while (stripe < drawEndX)
		{
			a->tex[id].texx = (int)(1.0 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * a->tex[id].width / spriteWidth);
			if(transformY > 0 && stripe > 0 && stripe < a->w && transformY < a->distbuff[stripe])
			{
				int y = drawStartY;
				while(y < drawEndY)
				{
					int d = (y - (a->h / 10) * (a->pl.dvy - 1)) * 256 - a->h * 128 + spriteHeight * 128;
					int texY = ((d * a->tex[id].height) / spriteHeight) / 256;
					int color = ft_getcolor(texY, a->tex[id]);
					ft_putpixel(stripe, y, a, color);
					y++;
				}
			}
			stripe++;
		}
	}
	drawhud(a);
	mlx_put_image_to_window(a->data.mlx, a->data.win, (a->data).img, 0, 0);
	a->calc = 0;
}

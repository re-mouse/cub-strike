/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charmover.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:22:11 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 19:22:46 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	checkmoveface(t_all *a, float ms, float mult)
{
	float x;
	float y;

	x = (a->pl.dx * ms) * mult;
	y = (a->pl.dy * ms) * mult;
	if (a->map[(int)(a->pl.psx + x)][(int)a->pl.psy] == '0')
		a->pl.psx += x;
	if (a->map[(int)a->pl.psx][(int)(a->pl.psy + y)] == '0')
		a->pl.psy += y;
	if (a->map[(int)(a->pl.psx + x)][(int)a->pl.psy] == '4')
	{
		a->pl.psx += x;
		gethp(a);
	}
	if (a->map[(int)a->pl.psx][(int)(a->pl.psy + y)] == '4')
	{
		a->pl.psy += y;
		gethp(a);
	}
	if (a->map[(int)(a->pl.psx + x)][(int)a->pl.psy] == '3')
		getnextlevel(a, 1);
	if (a->map[(int)a->pl.psx][(int)(a->pl.psy + y)] == '3')
		getnextlevel(a, 1);
}

void	checkmoveside(t_all *a, float ms, float mult)
{
	float x;
	float y;

	x = a->pl.dx * cos(asin(mult)) - a->pl.dy * sin(asin(mult));
	y = a->pl.dx * sin(asin(mult)) + a->pl.dy * cos(asin(mult));
	if (a->map[(int)(a->pl.psx - x * ms)][(int)a->pl.psy] == '0')
		a->pl.psx -= x * ms;
	if (a->map[(int)a->pl.psx][(int)(a->pl.psy - y * ms)] == '0')
		a->pl.psy -= y * ms;
	if (a->map[(int)(a->pl.psx - x * ms)][(int)a->pl.psy] == '4')
	{
		a->pl.psx -= x * ms;
		gethp(a);
	}
	if (a->map[(int)a->pl.psx][(int)(a->pl.psy - y * ms)] == '4')
	{
		a->pl.psy -= y * ms;
		gethp(a);
	}
	if (a->map[(int)a->pl.psx][(int)(a->pl.psy - y * ms)] == '3')
		getnextlevel(a, 1);
	if (a->map[(int)(a->pl.psx - x * ms)][(int)a->pl.psy] == '3')
		getnextlevel(a, 1);
}

void	ft_movechar(t_all *a, int keycode, float ms)
{
	float		mult;

	mult = keycode == 2 || keycode == 0 ? -1.0 : 1.0;
	if (keycode == 1 || keycode == 2)
		checkmoveface(a, ms, mult);
	else
		checkmoveside(a, ms, mult);
}

int		unkey_hook(int keycode, t_all *a)
{
	if (keycode == 49)
		checkwhocandie(a);
	if (keycode == 0)
		a->ctrl.side_pressed[0] = 0;
	if (keycode == 13)
		a->ctrl.side_pressed[1] = 0;
	if (keycode == 1)
		a->ctrl.side_pressed[2] = 0;
	if (keycode == 2)
		a->ctrl.side_pressed[3] = 0;
	return (1);
}

int		key_hook(int keycode, t_all *a)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 0)
		a->ctrl.side_pressed[0] = 1;
	if (keycode == 13)
		a->ctrl.side_pressed[1] = 1;
	if (keycode == 1)
		a->ctrl.side_pressed[2] = 1;
	if (keycode == 2)
		a->ctrl.side_pressed[3] = 1;
	return (1);
}

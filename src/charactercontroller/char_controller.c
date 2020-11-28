/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:40:55 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/27 07:09:30 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	ft_rotatechar(t_all *a, float rotspeed)
{
	float odx;
	float opx;

	odx = a->pl.dx;
	a->pl.dx = a->pl.dx * cos(rotspeed) - a->pl.dy * sin(rotspeed);
	a->pl.dy = odx * sin(rotspeed) + a->pl.dy * cos(rotspeed);
	opx = a->pl.planex;
	a->pl.planex = a->pl.planex * cos(rotspeed) - a->pl.planey * sin(rotspeed);
	a->pl.planey = opx * sin(rotspeed) + a->pl.planey * cos(rotspeed);
}

int		mouseclickhook(int but, int x, int y, t_all *a)
{
	(void)x;
	(void)y;
	if (but == 1)
	{
		checkwhocandie(a);
		processmoblogic(a);
		castraycasts(a);
	}
	return (1);
}

void	ft_movechar(t_all *a, int keycode, float ms)
{
	double		mult;
	float		x;
	float		y;

	mult = keycode == 2 || keycode == 0 ? -1.0 : 1.0;
	if (keycode == 1 || keycode == 2)
	{
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
	else
	{
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
}

int		hook(t_all *a)
{
	int i;
	int	diff;
	int x;
	int y;

	mlx_mouse_get_pos(a->data.win, &x, &y);
	i = -1;
	while (++i < 4)
		if (a->ctrl.side_pressed[i])
		{
			ft_movechar(a, i, 0.07);
		}
	if (x != a->maxresx)
	{
		x = a->maxresx - x;
		ft_rotatechar(a, 0.0015 * x);
		mlx_mouse_move(a->data.win, a->maxresx, a->maxresy / 2);
	}
	if (y != a->ctrl.lasty && y != a->maxresy / 2)
	{
		diff = a->ctrl.lasty - y;
		a->pl.dvy += 0.016 * diff;
		if (!a->ctrl.usedy)
		{
			a->ctrl.usedy = 1;
			a->ctrl.firsty = y;
			a->pl.dvy = 1;
		}
		if (a->pl.dvy < -12)
			a->pl.dvy = -12;
		if (a->pl.dvy > 12)
			a->pl.dvy = 12;
		mlx_mouse_move(a->data.win, a->maxresx, a->maxresy / 2);
		mlx_mouse_get_pos(a->data.win, &x, &y);
		a->ctrl.lasty = y;
	}
	processmoblogic(a);
	castraycasts(a);
	if (a->ismultiplayer)
	{
		sendpacket(a);
		recievepacket(a);
	}
	return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:40:55 by hleilani          #+#    #+#             */
/*   Updated: 2020/12/01 16:20:18 by hleilani         ###   ########.fr       */
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

void	posthook(t_all *a, int x, int y)
{
	int diff;

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
		a->pl.dvy < -12 ? a->pl.dvy = -12 : 0;
		a->pl.dvy > 12 ? a->pl.dvy = 12 : 0;
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
}

int		hook(t_all *a)
{
	int i;
	int x;
	int y;

	mlx_mouse_get_pos(a->data.win, &x, &y);
	i = -1;
	while (++i < 4)
		a->ctrl.side_pressed[i] ? ft_movechar(a, i, 0.07) : 0;
	if (x != a->maxresx)
	{
		x = a->maxresx - x;
		ft_rotatechar(a, 0.0015 * x);
		mlx_mouse_move(a->data.win, a->maxresx, a->maxresy / 2);
	}
	posthook(a, x, y);
	a->screen > 0 ? a->screen-- : 0;
	a->screen == 1 ? takescreenshot(a) : 0;
	return (1);
}

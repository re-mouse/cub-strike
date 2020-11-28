/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:27:45 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/22 13:19:19 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	ft_fillpngdraw(t_all *a)
{
	if (a->pr.side == 0)
		a->pr.pwl = (a->pr.mx - a->pl.psx + (1 - a->pr.stepx) / 2) / a->pr.rdx;
	else
		a->pr.pwl = (a->pr.my - a->pl.psy + (1 - a->pr.stepy) / 2) / a->pr.rdy;
	a->dpr.lineheight = (int)(a->h / a->pr.pwl);
	a->dpr.drawstart = -a->dpr.lineheight / 2 + a->h / 2;
	if (a->dpr.drawstart < 0)
		a->dpr.drawstart = 0;
	a->dpr.drawend = a->dpr.lineheight / 2 + a->h / 2;
	if (a->dpr.drawend >= a->h)
		a->dpr.drawend = a->h - 1;
	if (a->pr.side == 1)
	{
		if (a->pr.my > a->pl.psy)
			a->pr.texi = 0;
		else
			a->pr.texi = 1;
	}
	else
	{
		if (a->pr.mx > a->pl.psx)
			a->pr.texi = 2;
		else
			a->pr.texi = 3;
	}
}

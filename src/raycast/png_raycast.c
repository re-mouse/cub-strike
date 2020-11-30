/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:27:45 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/29 14:54:36 by hleilani         ###   ########.fr       */
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
	a->dpr.drawstart < 0 ? a->dpr.drawstart = 0 : 0;
	a->dpr.drawend = a->dpr.lineheight / 2 + a->h / 2;
	a->dpr.drawend >= a->h ? a->dpr.drawend = a->h - 1 : 0;
	if (a->pr.side == 1)
	{
		a->pr.texi = a->pr.my > a->pl.psy ? 0 : 1;
	}
	else
	{
		a->pr.texi = a->pr.mx > a->pl.psx ? 2 : 3;
	}
}

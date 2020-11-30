/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendgetpackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:28:07 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 19:28:39 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	killunicid(t_all *a, int id)
{
	int i;

	i = 0;
	while (i < a->numsprites)
	{
		if (a->sprites[i].unicid == id)
		{
			a->sprites[i].deadsended = 0;
			a->sprites[i].spritestate = 7;
		}
		i++;
	}
}

void	updatehealthandnextlvl(t_all *a)
{
	int	nextlvl;
	int	healtheated;

	nextlvl = 0;
	healtheated = 0;
	read(a->sockfd, &healtheated, sizeof(int));
	if (healtheated)
	{
		read(a->sockfd, &a->lasthealtheatedx, sizeof(int));
		read(a->sockfd, &a->lasthealtheatedy, sizeof(int));
		killhealth(a, a->lasthealtheatedx, a->lasthealtheatedy);
	}
	read(a->sockfd, &nextlvl, sizeof(int));
	if (nextlvl)
	{
		getnextlevel(a, 0);
	}
}

void	updateplayervariables(t_all *a)
{
	read(a->sockfd, &a->mp.angle, sizeof(int));
	read(a->sockfd, &a->mp.x, sizeof(float));
	read(a->sockfd, &a->mp.y, sizeof(float));
}

void	recievepacket(t_all *a)
{
	int i;
	int diff;
	int	deads;

	updatehealthandnextlvl(a);
	updateplayervariables(a);
	deads = 0;
	read(a->sockfd, &deads, sizeof(int));
	while (deads > 0)
	{
		i = 0;
		read(a->sockfd, &i, sizeof(int));
		killunicid(a, i);
		deads--;
	}
	diff = a->mp.angle - a->pl.angle;
	if (abs(diff) < 12)
		a->mp.spritestate = 35;
	else if (abs(diff) < 90)
		a->mp.spritestate = diff < 0 ? 33 : 34;
	else if (abs(diff) < 150)
		a->mp.spritestate = diff < 0 ? 31 : 32;
	else
		a->mp.spritestate = 30;
}

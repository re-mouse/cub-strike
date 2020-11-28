/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mobshoot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:15:04 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/27 07:30:18 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	gethp(t_all *a)
{
	a->pl.health += 15;
	if (a->pl.health > 100)
		a->pl.health = 100;
	a->healtheated = 1;
	a->lasthealtheatedx = a->pl.psx;
	a->lasthealtheatedy = a->pl.psy;
	killhealth(a, (int)a->pl.psx, (int)a->pl.psy);
}

void	killhealth(t_all *a, int x, int y)
{
	int i;

	i = -1;
	a->map[x][y] = '0';
	while (++i < a->numsprites)
	{
		if ((int)a->sprites[i].x == x && (int)a->sprites[i].y == y)
		{
			a->sprites[i].alive = 0;
		}
	}
}

void	checkwhocandie(t_all *a)
{
	int i;
	int pid;

	i = -1;
	if (a->pl.shootcd <= 0)
	{
		while (++i < a->numsprites)
			if (a->sprites[i].candie == 1 && a->sprites[i].spritestate < 7)
			{
				a->pl.score += 5;
				a->sprites[i].spritestate = 7;
				if (a->ismultiplayer)
					a->enemydied++;
				a->sprites[i].deadsended = 1;
			}
		a->hudpart[1].texid = 12;
		a->pl.shootcd = 1;
		pid = fork();
		(pid == 0) ? system("afplay ./sound/shoot.wav -v 1") : 0;
	}
}

void	checkplhp(t_all *a)
{
	if (a->pl.health <= 0)
		a->hudpart[2].dontdraw = 0;
}

void	checkcooldown(t_all *a, int i)
{
	int pid;
	a->sprites[i].spritestate = 5;
	if (a->sprites[i].shootcd <= 0)
	{
		a->sprites[i].shootcd = 2;
		a->sprites[i].spritestate = 6;
		pid = fork();
		(pid == 0) ? system("afplay ./sound/shoot.wav -v 0.5") : 0;
		a->pl.health -= 5;
		checkplhp(a);
	}
}

void	proccesdying(t_all *a, int i)
{
	if (a->sprites[i].spritestate < 10)
		a->sprites[i].spritestate++;
	if (a->sprites[i].spritestate == 10)
	{
		a->map[(int)a->sprites[i].x][(int)a->sprites[i].y] = '0';
		a->sprites[i].alive = 0;
	}
}

void	processmoblogic(t_all *a)
{
	time_t timer;
	int i;

	i = -1;
	timer = time(NULL);
	if (a->prev != timer)
	{
		a->pl.shootcd--;
		if (a->pl.shootcd <= 0)
			a->hudpart[1].texid = 11;
		while (++i < a->numsprites)
		{
			if (!a->sprites[i].alive)
				continue ;
			if (a->sprites[i].spritestate >= 7)
			{
				proccesdying(a, i);
				continue ;
			}
			a->sprites[i].shootcd--;
			a->sprites[i].spritestate = 4;
			if (a->sprites[i].seepl)
				checkcooldown(a, i);
		}
	}
	a->prev = timer;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chekcs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:26:58 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 19:27:04 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	checkwhocandie(t_all *a)
{
	int i;

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
	}
}

void	checkplhp(t_all *a)
{
	if (a->pl.health <= 0)
		a->hudpart[2].dontdraw = 0;
}

void	checkcooldown(t_all *a, int i)
{
	a->sprites[i].spritestate = 5;
	if (a->sprites[i].shootcd <= 0)
	{
		a->sprites[i].shootcd = 2;
		a->sprites[i].spritestate = 6;
		a->pl.health -= 5;
		checkplhp(a);
	}
}

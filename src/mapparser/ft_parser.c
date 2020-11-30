/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:25:18 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 19:06:48 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

int		ft_is_validezero(char **map, int x, int y)
{
	if (map[y][x] != '0')
		return (1);
	if (!ft_is_map(map[y + 1][x]))
		return (0);
	if (!ft_is_map(map[y - 1][x]))
		return (0);
	if (!ft_is_map(map[y][x + 1]))
		return (0);
	if (!ft_is_map(map[y][x - 1]))
		return (0);
	return (1);
}

int		setspritesettings(t_all *a, int i, int x, int y)
{
	if (a->map[y][x] == '2')
	{
		a->sprites[i].unicid = i;
		a->sprites[i].x = y + 0.5;
		a->sprites[i].y = x + 0.5;
		a->sprites[i].shootcd = 1;
		a->sprites[i].spritestate = 4;
		a->sprites[i].alive = 1;
		return (1);
	}
	else if (a->map[y][x] == '4')
	{
		a->sprites[i].unicid = i;
		a->sprites[i].x = y + 0.5;
		a->sprites[i].y = x + 0.5;
		a->sprites[i].shootcd = 9999;
		a->sprites[i].spritestate = 17;
		a->sprites[i].alive = 1;
		return (1);
	}
	return (0);
}

void	parse_final_map(t_all *a)
{
	int		y;
	int		x;
	int		i;

	i = 0;
	y = -1;
	while (++y < (int)a->mapheight)
	{
		x = -1;
		while (++x < (int)ft_strlen(a->map[y]))
		{
			!is_part_ofmap(a->map[y][x]) || !ft_is_validezero(a->map, x, y) ?
			ft_throwerror("You have space with zero or unvaliable char") : 0;
			setspritesettings(a, i, x, y) ? i++ : 0;
			if (a->map[y][x] == 'N')
			{
				if (a->pl.psx != -1)
					ft_throwerror("Multiple player error");
				a->pl.psy = x + 0.5;
				a->pl.psx = y + 0.5;
				a->map[y][x] = '0';
			}
		}
	}
}

void	find_maxwidthmap(t_all *all)
{
	int		yscale;
	int		xscale;
	size_t	maxlength;
	size_t	y;
	size_t	temp;

	y = 0;
	maxlength = 0;
	while (y < all->mapheight)
	{
		temp = ft_strlen(all->map[y]);
		maxlength = temp > maxlength ? temp : maxlength;
		y++;
	}
	yscale = all->resolution_height / all->mapheight;
	xscale = all->resolution_width / maxlength;
	all->mapwidth = maxlength;
	if (xscale > yscale)
		all->resolution_scalepixel = yscale;
	else
		all->resolution_scalepixel = xscale;
}

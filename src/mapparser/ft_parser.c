/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:25:18 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/27 06:59:50 by hleilani         ###   ########.fr       */
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

void	parse_final_map(t_all *all)
{
	int		y;
	int		x;
	char	**map;
	int		i;

	i = 0;
	y = -1;
	map = all->map;
	while (++y < (int)all->mapheight)
	{
		x = -1;
		while (++x < (int)ft_strlen(map[y]))
		{
			if (!is_part_ofmap(map[y][x]) || !ft_is_validezero(map, x, y))
				ft_throwerror("You have space with zero or unvaliable char");
			if (map[y][x] == '2')
			{
				all->sprites[i].unicid = i;
				all->sprites[i].x = y + 0.5;
				all->sprites[i].y = x + 0.5;
				all->sprites[i].shootcd = 1;
				all->sprites[i].spritestate = 4;
				all->sprites[i].alive = 1;
				i++;
			}
			else if (map[y][x] == '4')
			{
				all->sprites[i].unicid = i;
				all->sprites[i].x = y + 0.5;
				all->sprites[i].y = x + 0.5;
				all->sprites[i].shootcd = 9999;
				all->sprites[i].spritestate = 17;
				all->sprites[i].alive = 1;
				i++;
			}
			if (map[y][x] == 'N')
			{
				if (all->pl.psx != -1)
					ft_throwerror("Multiple player error");
				all->pl.psy = x + 0.5;
				all->pl.psx = y + 0.5;
				map[y][x] = '0';
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_resol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:06:18 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/22 21:28:06 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	ft_correctresolution(t_all *all)
{
	int x;
	int y;

	mlx_get_screen_size(all->data.mlx, &x, &y);
	all->maxresx = x / 2;
	all->maxresy = y / 2;
	if ((int)all->resolution_height > y)
		all->resolution_height = y;
	if ((int)all->resolution_width > x)
		all->resolution_width = x;
}

int		parse_resolution(t_all *all, char *line)
{
	char *temp;

	temp = line;
	if (*line != 'R')
		return (0);
	line++;
	if (*line++ != ' ')
		ft_throwerror("Resolution parse error");
	while (*line == ' ')
		line++;
	all->resolution_width = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line++ != ' ' || all->resolution_width <= 0)
		ft_throwerror("Resolution width missing");
	while (*line == ' ')
		line++;
	all->resolution_height = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line != '\0' || all->resolution_height <= 0)
		ft_throwerror("Resolution height missing");
	ft_correctresolution(all);
	free(temp);
	return (1);
}

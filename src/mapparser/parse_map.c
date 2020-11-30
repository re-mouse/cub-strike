/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:34:25 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 20:18:14 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	countmaplinesfunc(t_all *a, int fd, int *i)
{
	char *line;
	char *temp;

	while (get_next_line(fd, &line) > 0)
	{
		*i += 1;
		temp = line;
		if (!is_map(line))
			ft_throwerror("Wrong chars in map");
		while (*line)
		{
			(*line == '2' || *line == '4') && *line ? a->numsprites++ : 0;
			line++;
		}
		free(temp);
	}
	temp = line;
	!is_map(line) ? ft_throwerror("Wrong chars in map") : 0;
	while (*line)
	{
		(*line == '2' || *line == '4') && *line ? a->numsprites++ : 0;
		line++;
	}
	free(temp);
	*i += 1;
}

int		count_maplines(char *map, t_all *a)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(map, O_RDONLY);
	while (get_next_line(fd, &line) > 0 && !is_map(line))
		free(line);
	if (is_map(line))
	{
		i++;
		free(line);
		countmaplinesfunc(a, fd, &i);
	}
	close(fd);
	return (i);
}

int		isthisnextmap(t_all *a, char *l)
{
	if (ft_strncmp(l, "NEXTLEVEL ", 10))
		return (0);
	a->nextmap = ft_strdup(l + 10);
	free(l);
	return (1);
}

void	allocate_map(t_all *all, char *map, int fd)
{
	int count;

	if (fd < 0)
		ft_throwerror("Can't open map, does it exist?");
	count = count_maplines(map, all);
	all->map = ft_calloc(count + 1, sizeof(char*));
	all->map[count] = NULL;
	all->mapheight = count;
	all->pl.psx = -1;
	all->pl.psy = -1;
	if (all->sprites != NULL)
	{
		free(all->sprites);
		all->sprites = NULL;
	}
	all->sprites = ft_calloc(all->numsprites + 1, sizeof(t_sprite));
}

int		get_map(t_all *all, char *map)
{
	int		fd;
	char	*line;

	all->nextmap = NULL;
	all->numsprites = 0;
	fd = open(map, O_RDONLY);
	allocate_map(all, map, fd);
	while (get_next_line(fd, &line) > 0 && !is_map(line))
	{
		if (parse_resolution(all, line) || ft_parse_texture(all, line))
			continue ;
		else if (isthisnextmap(all, line) || ft_parse_color(line, all))
			continue ;
		if (*line != '\0')
			ft_throwerror("Unvaliable settings in map config");
		free(line);
	}
	ft_fillmap(all, line, fd);
	find_maxwidthmap(all);
	parse_final_map(all);
	if (all->pl.psx == -1)
		ft_throwerror("Missing player error");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:34:25 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/27 06:58:24 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

int		count_maplines(char *map, t_all *a)
{
	int		i;
	int		fd;
	char	*line;
	char	*temp;

	i = 0;
	fd = open(map, O_RDONLY);
	while (get_next_line(fd, &line) > 0 && !is_map(line))
		free(line);
	if (is_map(line))
	{
		i++;
		free(line);
		while (get_next_line(fd, &line) > 0)
		{
			i++;
			temp = line;
			if (!is_map(line))
				ft_throwerror("Wrong chars in map");
			while (*line)
			{
				if ((*line == '2' || *line == '4') && *line)
					a->numsprites++;
				line++;
			}
			free(temp);
		}
		temp = line;
		if (!is_map(line))
			ft_throwerror("Wrong chars in map");
		while (*line)
		{
			if ((*line == '2' || *line == '4') && *line)
				a->numsprites++;
			line++;
		}
		free(temp);
		i++;
	}
	close(fd);
	return (i);
}

void	ft_fillmap(t_all *all, char *line, int fd)
{
	int i;
	int res;

	i = 0;
	if (is_map(line))
	{
		all->map[i++] = ft_strdup(line);
		free(line);
		while ((res = get_next_line(fd, &line)) > 0)
		{
			if (!is_map(line))
				ft_throwerror("Unvaliable map error");
			all->map[i++] = ft_strdup(line);
			free(line);
		}
		if (res == 0)
		{
			if (!is_map(line))
				ft_throwerror("Unvaliable map error");
			all->map[i++] = ft_strdup(line);
			free(line);
		}
	}
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
	if (all->sprites == NULL)
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
		if (parse_resolution(all, line))
			continue ;
		else if (ft_parse_texture(all, line))
			continue ;
		else if (isthisnextmap(all, line))
			continue ;
		else if (ft_parse_color(line, all))
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

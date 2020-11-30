/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textureparser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:23:15 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 19:26:37 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	intializehud(t_all *a)
{
	a->hudpart[0].texid = 10;
	a->hudpart[0].x = 0.47;
	a->hudpart[0].y = 0.47;
	a->hudpart[0].percent = 0.05;
	a->hudpart[1].texid = 10;
	a->hudpart[1].x = 0.2;
	a->hudpart[1].y = 0.4;
	a->hudpart[1].percent = 0.6;
	a->hudpart[2].texid = 15;
	a->hudpart[2].x = 0;
	a->hudpart[2].y = 0;
	a->hudpart[2].percent = 1;
	a->hudpart[2].dontdraw = 1;
}

void	settexture(t_all *a)
{
	a->tex[5].texfilename = "./textures/st2.xpm";
	a->tex[5].valide = 1;
	a->tex[6].texfilename = "./textures/st3.xpm";
	a->tex[6].valide = 1;
	a->tex[7].texfilename = "./textures/st4.xpm";
	a->tex[7].valide = 1;
	a->tex[8].texfilename = "./textures/st5.xpm";
	a->tex[8].valide = 1;
	a->tex[9].texfilename = "./textures/st6.xpm";
	a->tex[9].valide = 1;
	a->tex[10].texfilename = "./textures/chr2.xpm";
	a->tex[10].valide = 1;
	a->tex[11].texfilename = "./textures/PR.xpm";
	a->tex[11].valide = 1;
	a->tex[12].texfilename = "./textures/PF.xpm";
	a->tex[12].valide = 1;
	a->tex[13].texfilename = "./textures/wall.xpm";
	a->tex[13].valide = 1;
	a->tex[16].texfilename = "./textures/test1.xpm";
	a->tex[16].valide = 1;
	a->tex[17].texfilename = "./textures/hp.xpm";
	a->tex[17].valide = 1;
}

int		ft_parse_texture(t_all *a, char *l)
{
	int		i;
	char	*temp;

	temp = l;
	i = -1;
	ft_strncmp(l, "NO ", 3) == 0 ? i = 0 : 0;
	ft_strncmp(l, "SO ", 3) == 0 ? i = 1 : 0;
	ft_strncmp(l, "WE ", 3) == 0 ? i = 2 : 0;
	ft_strncmp(l, "EA ", 3) == 0 ? i = 3 : 0;
	ft_strncmp(l, "S ", 2) == 0 ? i = 4 : 0;
	ft_strncmp(l, "FL ", 3) == 0 ? i = 14 : 0;
	ft_strncmp(l, "EG ", 3) == 0 ? i = 15 : 0;
	if (i == -1)
		return (0);
	l += 2;
	while (*l == ' ')
		l++;
	a->tex[i].texfilename = ft_strjoin(l, ".xpm");
	a->tex[i].valide = 1;
	free(temp);
	return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:53:54 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/27 06:40:33 by hleilani         ###   ########.fr       */
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

int		ft_parse_texture(t_all *a, char *l)
{
	int		i;
	char	*temp;

	temp = l;
	i = -1;
	if (ft_strncmp(l, "NO", 2) == 0)
		i = 0;
	else if (ft_strncmp(l, "SO", 2) == 0)
		i = 1;
	else if (ft_strncmp(l, "WE", 2) == 0)
		i = 2;
	else if (ft_strncmp(l, "EA", 2) == 0)
		i = 3;
	else if (ft_strncmp(l, "S ", 2) == 0)
		i = 4;
	else if (ft_strncmp(l, "S1", 2) == 0)
		i = 5;
	else if (ft_strncmp(l, "S2", 2) == 0)
		i = 6;
	else if (ft_strncmp(l, "S3", 2) == 0)
		i = 7;
	else if (ft_strncmp(l, "S4", 2) == 0)
		i = 8;
	else if (ft_strncmp(l, "S5", 2) == 0)
		i = 9;
	else if (ft_strncmp(l, "TR", 2) == 0)
		i = 10;
	else if (ft_strncmp(l, "PR", 2) == 0)
		i = 11;
	else if (ft_strncmp(l, "PT", 2) == 0)
		i = 12;
	else if (ft_strncmp(l, "NT", 2) == 0)
		i = 13;
	else if (ft_strncmp(l, "FL", 2) == 0)
		i = 14;
	else if (ft_strncmp(l, "EG", 2) == 0)
		i = 15;
	else if (ft_strncmp(l, "NG", 2) == 0)
		i = 16;
	else if (ft_strncmp(l, "HP", 2) == 0)
		i = 17;
	else
		return (0);
	l += 2;
	while (*l == ' ')
		l++;
	a->tex[i].texfilename = ft_strjoin(l, ".xpm");
	a->tex[i].valide = 1;
	free(temp);
	return (1);
}

void	ft_insertnumbers(t_all *a)
{
	int		*t1;
	int		*t2;
	void	*t;
	int		fd;
	char	*t3;
	int i;

	i = 19;
	while (++i < 30)
	{
		t = ft_itoa(i - 20);
		t3 = ft_strjoin("./cifri/", t);
		free(t);
		a->tex[i].texfilename = ft_strjoin(t3, ".xpm");
		free(t3);
		t1 = &a->tex[i].width;
		t2 = &a->tex[i].height;
		if ((fd = open(a->tex[i].texfilename, O_RDONLY)) < 0)
			ft_throwerror("Missing numbers png");
		close(fd);
		t = mlx_xpm_file_to_image(a->data.mlx, a->tex[i].texfilename, t1, t2);
		a->tex[i].img = t;
		t1 = &(a->tex[i].bpp);
		t2 = &(a->tex[i].line_len);
		t = mlx_get_data_addr(a->tex[i].img, t1, t2, &(a->tex[i].endian));
		a->tex[i].addr = t;
	}
}

void	ft_insertmult(t_all *a)
{
	int		*t1;
	int		*t2;
	void	*t;
	int		fd;
	char	*t3;
	int i;

	i = 29;
	while (++i < 36)
	{
		t = ft_itoa(i - 30);
		t3 = ft_strjoin("./mult/", t);
		free(t);
		a->tex[i].texfilename = ft_strjoin(t3, ".xpm");
		free(t3);
		t1 = &a->tex[i].width;
		t2 = &a->tex[i].height;
		if ((fd = open(a->tex[i].texfilename, O_RDONLY)) < 0)
			ft_throwerror("Missing numbers png");
		close(fd);
		t = mlx_xpm_file_to_image(a->data.mlx, a->tex[i].texfilename, t1, t2);
		a->tex[i].img = t;
		t1 = &(a->tex[i].bpp);
		t2 = &(a->tex[i].line_len);
		t = mlx_get_data_addr(a->tex[i].img, t1, t2, &(a->tex[i].endian));
		a->tex[i].addr = t;
	}
}

int		ft_inserttextdata(t_all *a)
{
	int		i;
	int		fd;
	int		*t1;
	int		*t2;
	void	*t;

	i = 0;
	while (i < 18)
	{
		t1 = &a->tex[i].width;
		t2 = &a->tex[i].height;
		if ((fd = open(a->tex[i].texfilename, O_RDONLY)) < 0)
			ft_throwerror("Missing texture, or can't open it");
		close(fd);
		t = mlx_xpm_file_to_image(a->data.mlx, a->tex[i].texfilename, t1, t2);
		a->tex[i].img = t;
		t1 = &(a->tex[i].bpp);
		t2 = &(a->tex[i].line_len);
		t = mlx_get_data_addr(a->tex[i].img, t1, t2, &(a->tex[i].endian));
		a->tex[i].addr = t;
		i++;
	}
	ft_insertnumbers(a);
	ft_insertmult(a);
	intializehud(a);
	return (1);
}

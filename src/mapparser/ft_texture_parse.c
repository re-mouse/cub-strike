/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:53:54 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 16:35:10 by hleilani         ###   ########.fr       */
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

char	*createpath(int i, char *path)
{
	char *t;
	char *t3;
	char *nt;

	t = ft_itoa(i);
	t3 = ft_strjoin(path, t);
	free(t);
	nt = ft_strjoin(t3, ".xpm");
	free(t3);
	return (nt);
}

void	ft_insertnumbers(t_all *a)
{
	int		*t1;
	int		*t2;
	void	*t;
	int		fd;
	int		i;

	i = 19;
	while (++i < 30)
	{
		a->tex[i].texfilename = createpath(i - 20, "./cifri/");
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
	int		i;

	i = 29;
	while (++i < 36)
	{
		a->tex[i].texfilename = createpath(i - 30, "./mult/");
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

void	posttextdata(t_all *a)
{
	ft_insertnumbers(a);
	ft_insertmult(a);
	intializehud(a);
}

int		ft_inserttextdata(t_all *a)
{
	int		i;
	int		fd;
	int		*t1;
	int		*t2;
	void	*t;

	i = 0;
	settexture(a);
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
	posttextdata(a);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:53:54 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 19:23:53 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

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

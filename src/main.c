/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:03:57 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/27 07:30:10 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_cub.h"

void	ft_throwerror(char *message)
{
	ft_putendl_fd(message, 2);
	exit(2);
}

void	set_default(t_all *a)
{
	a->h = a->resolution_height;
	a->w = a->resolution_width;
	a->pl.dx = -1;
	a->pl.dy = 0;
	a->pl.planex = 0;
	a->pl.planey = 0.5;
	a->pl.dvy = 1.0;
	a->pl.health = 100;
	a->pl.shootcd = 0;
	a->pl.score = 0;
	a->prev = time(NULL);
}

int		check(void)
{
	ft_putendl_fd("Thx for playing :)", 1);
	exit(0);
}

void	ft_getdataaddr(t_all *a)
{
	int	*t;
	int	*s;
	int	*h;

	t = &(a->data.bits_per_pixel);
	s = &(a->data.line_length);
	h = &(a->data.endian);
	a->data.addr = mlx_get_data_addr(a->data.img, t, s, h);
}

int		main(int argc, char **argv)
{
	char	**mapl;
	t_all	*a;
	size_t	tmf;
	size_t	tms;
	int		pid;

	a = ft_calloc(1, sizeof(t_all));
	if (argc < 2)
		ft_throwerror("No map argument error");
	if (argc > 2 && !ft_strncmp(argv[2], "host", 4))
	{
		if (argc != 4)
			ft_throwerror("Missing port");
		a->port = ft_atoi(argv[3]);
		createserver(a);
	}
	if (argc > 2 && !ft_strncmp(argv[2], "client", 6))
	{
		if (argc != 5)
			ft_throwerror("Missing ip or port (ip first)");
		a->port = ft_atoi(argv[4]);
		a->ip = argv[3];
		connectserver(a);
	}
	get_map(a, argv[1]);
	mapl = a->map;
	set_default(a);
	a->data.mlx = mlx_init();
	tmf = a->resolution_width;
	tms = a->resolution_height;
	a->data.win = mlx_new_window(a->data.mlx, tmf, tms, "Terminator Timofey");
	a->data.img = mlx_new_image(a->data.mlx, tmf, tms);
	ft_getdataaddr(a);
	ft_inserttextdata(a);
	a->distbuff = ft_calloc(a->w + 1, sizeof(float));
	pid = fork();
	(pid == 0) ? system("afplay ./sound/music.wav -v 0.5") : 0;
	castraycasts(a);
	mlx_mouse_move(a->data.win, a->w / 2, a->h / 2);
	mlx_hook(a->data.win, 2, 1L << 0, key_hook, a);
	mlx_hook(a->data.win, 3, 1L << 1, unkey_hook, a);
	mlx_hook(a->data.win, 17, 1L << 17, check, NULL);
	mlx_mouse_hook(a->data.win, mouseclickhook, a);
	mlx_loop_hook(a->data.mlx, hook, a);
	
	mlx_loop(a->data.mlx);
}

void	freedata(t_all *a)
{
	int i;

	i = -1;
	while (a->map[++i] != NULL)
		free(a->map[i]);
	i = -1;
	while (a->tex[++i].texfilename != NULL)
		free(a->tex[i].texfilename);
	free(a->map);
}

void	getnextlevel(t_all *a, int send)
{
	char *temp;

	if (send && a->nextlvltriger == 0)
	{
		a->nextlvltriger = 1;
		a->mp.alive = 0;
	}
	else
		a->nextlvltriger = 0;
	if (a->nextmap == NULL)
	{
		ft_putendl_fd("You won 🥳!", 1);
		exit(0);
	}
	freedata(a);
	temp = a->nextmap;
	ft_putendl_fd("Starting getting map", 1);
	get_map(a, a->nextmap); 
	a->mp.x = a->pl.psx;
	a->mp.y = a->pl.psy;
	free(temp);
}
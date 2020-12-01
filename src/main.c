/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:03:57 by hleilani          #+#    #+#             */
/*   Updated: 2020/12/01 17:01:45 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_cub.h"

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

void	firstintialization(t_all *a)
{
	size_t	tmf;
	size_t	tms;

	a->data.mlx = mlx_init();
	tmf = a->resolution_width;
	tms = a->resolution_height;
	a->data.win = mlx_new_window(a->data.mlx, tmf, tms, "Terminator Timofey");
	a->data.img = mlx_new_image(a->data.mlx, tmf, tms);
	ft_getdataaddr(a);
	ft_inserttextdata(a);
	a->distbuff = ft_calloc(a->w + 1, sizeof(float));
	castraycasts(a);
	mlx_mouse_move(a->data.win, a->w / 2, a->h / 2);
	mlx_hook(a->data.win, 2, 1L << 0, key_hook, a);
	mlx_hook(a->data.win, 3, 1L << 1, unkey_hook, a);
	mlx_hook(a->data.win, 17, 1L << 17, check, NULL);
	mlx_mouse_hook(a->data.win, mouseclickhook, a);
	mlx_loop_hook(a->data.mlx, hook, a);
	mlx_loop(a->data.mlx);
}

void	checkargs(int argc, char **argv)
{
	if (argc < 2)
		ft_throwerror("No map argument error");
	if (argc > 2)
	{
		if (!ft_strncmp(argv[2], "host", 5)
		|| !ft_strncmp(argv[2], "client", 7)
		|| !ft_strncmp(argv[2], "--save", 7))
			return ;
		else
			ft_throwerror("Invalid second argument");
	}
}

int		main(int argc, char **argv)
{
	char	**mapl;
	t_all	*a;

	a = ft_calloc(1, sizeof(t_all));
	argc < 2 ? ft_throwerror("No map argument error") : 0;
	checkargs(argc, argv);
	if (argc > 2 && !ft_strncmp(argv[2], "host", 5))
	{
		argc != 4 ? ft_throwerror("Missing port") : 0;
		a->port = ft_atoi(argv[3]);
		createserver(a);
	}
	if (argc > 2 && !ft_strncmp(argv[2], "client", 7))
	{
		argc != 5 ? ft_throwerror("Missing ip or port (ip first)") : 0;
		a->port = ft_atoi(argv[4]);
		a->ip = argv[3];
		connectserver(a);
	}
	playsound(a, "afplay ./sound/music.wav");
	argc > 2 && !ft_strncmp(argv[2], "--save", 7) ? a->screen = 20 : 0;
	get_map(a, argv[1]);
	mapl = a->map;
	set_default(a);
	firstintialization(a);
}

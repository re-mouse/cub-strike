/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:03:57 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 13:21:23 by hleilani         ###   ########.fr       */
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

int		main(int argc, char **argv)
{
	char	**mapl;
	t_all	*a;

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
	firstintialization(a);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:00:47 by hleilani          #+#    #+#             */
/*   Updated: 2020/12/01 17:03:17 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_cub.h"

unsigned char	g_bfh[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
unsigned char	g_bih[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
unsigned char	g_bmppad[3] = {0, 0, 0};
int				g_filesize;
int				g_d;
int				g_i;
int				g_x;

void	playsound(t_all *a, char *command)
{
	int pid;

	(void)a;
	pid = fork();
	(pid == 0) ? system(command) : 0;
	(pid == 0) ? exit(0) : 0;
}

void	takescreenshot(t_all *a)
{
	g_filesize = 54 + 3 * a->w * a->h;
	g_bfh[2] = (unsigned char)(g_filesize);
	g_bfh[3] = (unsigned char)(g_filesize >> 8);
	g_bfh[4] = (unsigned char)(g_filesize >> 16);
	g_bfh[5] = (unsigned char)(g_filesize >> 24);
	g_bih[4] = (unsigned char)(a->w);
	g_bih[5] = (unsigned char)(a->w >> 8);
	g_bih[6] = (unsigned char)(a->w >> 16);
	g_bih[7] = (unsigned char)(a->w >> 24);
	g_bih[8] = (unsigned char)(a->h);
	g_bih[9] = (unsigned char)(a->h >> 8);
	g_bih[10] = (unsigned char)(a->h >> 16);
	g_bih[11] = (unsigned char)(a->h >> 24);
	(g_d = open("screen.bmp", O_CREAT | O_RDWR, 0644));
	1 ? write(g_d, g_bfh, 14) && write(g_d, g_bih, 40) : 0;
	g_d > 0 ? g_i = a->h : ft_throwerror("Screenshot file error");
	while (--g_i >= 0)
	{
		g_x = -1;
		while (++g_x < a->w)
			write(g_d, a->data.addr + (g_i * a->data.line_length +
			g_x * (a->data.bits_per_pixel / 8)), 3);
		write(g_d, g_bmppad, (4 - (a->w * 3) % 4) % 4);
	}
	close(g_d);
}

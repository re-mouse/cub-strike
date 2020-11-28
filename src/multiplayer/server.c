/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:17:19 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/27 07:12:35 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	createserver(t_all *a)
{
	socklen_t	len;
	int			sockfd;
	SI			cli;

	a->ismultiplayer = 1;
	ft_putendl_fd("Creating socket", 1);
	(sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ? ft_throwerror("Sk r") : 0;
	a->sock.sin_family = AF_INET;
	a->sock.sin_addr.s_addr = htonl(INADDR_ANY);
	a->sock.sin_port = htons(a->port);
	ft_putendl_fd("Binding socket", 1);
	bind(sockfd, (SA*)&a->sock, sizeof(a->sock)) ? ft_throwerror("SOC ER") : 0;
	ft_putendl_fd("Waiting player", 1);
	listen(sockfd, 5) ? ft_throwerror("Listening error") : 0;
	len = sizeof(cli);
	a->sockfd = accept(sockfd, (SA*)&a->sock, &len);
	ft_putendl_fd("Player connected", 1);
	sendpacket(a);
	postmultiplayer(a);
}

void	sendpacket(t_all *a)
{
	int i;

	write(a->sockfd, &a->healtheated, sizeof(int));
	if (a->healtheated)
	{
		write(a->sockfd, &a->lasthealtheatedx, sizeof(int));
		write(a->sockfd, &a->lasthealtheatedy, sizeof(int));
	}
	if (a->alivesended == 1)
	{
		a->mp.alive = 1;
		a->alivesended = 0;
	}
	write(a->sockfd, &a->nextlvltriger, sizeof(int));
	if (a->nextlvltriger)
	{
		a->nextlvltriger = 0;
		a->alivesended = 1;
	}
	i = 0;
	a->pl.angle = 57.2958 * atan2(a->pl.dx, a->pl.dy);
	a->pl.angle < 0 ? a->pl.angle += 360: 0;
	write(a->sockfd, &a->pl.angle, sizeof(int));
	write(a->sockfd, &a->pl.psx, sizeof(float));
	write(a->sockfd, &a->pl.psy, sizeof(float));
	write(a->sockfd, &a->enemydied, sizeof(int));
	if (a->enemydied)
		while (i < a->numsprites)
		{
			if (a->sprites[i].deadsended == 1)
			{
				write(a->sockfd, &a->sprites[i].unicid, sizeof(int));
				a->sprites[i].deadsended = 0;		
			}
			i++;
		}
	a->enemydied = 0;
}

void	killunicid(t_all *a, int id)
{
	int i;

	i = 0;
	while (i < a->numsprites)
	{
		if (a->sprites[i].unicid == id)
		{
			a->sprites[i].deadsended = 0;
			a->sprites[i].spritestate = 7;
		}
		i++;
	}
}

void	recievepacket(t_all *a)
{
	int i;
	int diff;
	int	deads;
	int	nextlvl;
	int	healtheated;

	nextlvl = 0;
	healtheated = 0;
	read(a->sockfd, &healtheated, sizeof(int));
	if (healtheated)
	{
		read(a->sockfd, &a->lasthealtheatedx, sizeof(int));
		read(a->sockfd, &a->lasthealtheatedy, sizeof(int));
		killhealth(a, a->lasthealtheatedx, a->lasthealtheatedy);
	}
	read(a->sockfd, &nextlvl, sizeof(int));
	if (nextlvl)
	{
		getnextlevel(a, 0);
	}
	read(a->sockfd, &a->mp.angle, sizeof(int));
	read(a->sockfd, &a->mp.x, sizeof(float));
	read(a->sockfd, &a->mp.y, sizeof(float));
	deads = 0;
	read(a->sockfd, &deads, sizeof(int));
	while (deads > 0)
	{
		i = 0;
		read(a->sockfd, &i, sizeof(int));
		killunicid(a, i);
		deads--;
	}
	diff = a->mp.angle - a->pl.angle;
	if (abs(diff) < 12)
		a->mp.spritestate = 35;
	else if (abs(diff) < 90)
		a->mp.spritestate = diff < 0 ? 33 : 34;
	else if (abs(diff) < 150)
		a->mp.spritestate = diff < 0 ? 31 : 32;
	else
		a->mp.spritestate = 30;
}

void	postmultiplayer(t_all *a)
{
	if (!a->ismultiplayer)
		return ;
	a->mp.alive = 1;
	a->mp.spritestate = 4;
}

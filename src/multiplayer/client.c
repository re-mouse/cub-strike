/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:17:11 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/30 16:02:48 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

void	connectserver(t_all *a)
{
	a->ismultiplayer = 1;
	ft_putendl_fd("Creating socket", 1);
	(a->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ?
	ft_throwerror("Sk r") : 0;
	a->sock.sin_family = AF_INET;
	a->sock.sin_addr.s_addr = inet_addr(a->ip);
	a->sock.sin_port = htons(a->port);
	ft_putendl_fd("Connecting to server", 1);
	connect(a->sockfd, (SA*)&a->sock, sizeof(a->sock)) ?
	ft_throwerror("CER") : 0;
	ft_putendl_fd("Connection succesful", 1);
	recievepacket(a);
	postmultiplayer(a);
}

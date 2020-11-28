/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplelogic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 13:05:44 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/27 07:00:25 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

int		is_part_ofmap(char c)
{
	return ((c >= '0' && c <= '4') || c == 'N' || c == ' ');
}

int		ft_is_map(char c)
{
	return ((c >= '0' && c <= '4') || c == 'N');
}

int		is_map(char *line)
{
	while (*line == ' ')
		line++;
	return (ft_isdigit(*line));
}

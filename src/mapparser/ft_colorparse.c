/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colorparse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:12:33 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/22 13:12:28 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cub.h"

int		ft_set_colors(int r, int g, int b, unsigned *cont)
{
	if (b > 255 || g > 255 || r > 255)
		ft_throwerror("Color more than 255 error");
	if (b < 0 || g < 0 || r < 0)
		ft_throwerror("Color under zero error");
	*cont += b % 16;
	*cont += b / 16 * 16;
	*cont += (int)pow(16, 2) * g % 16;
	*cont += (int)pow(16, 3) * g / 16;
	*cont += (int)pow(16, 4) * r % 16;
	*cont += (int)pow(16, 5) * r / 16;
	return (1);
}

char	*ft_skipdigitspace_comma(char *l)
{
	while (ft_isdigit(*l))
		l++;
	while (*l == ' ')
		l++;
	if (*l++ != ',')
		ft_throwerror("Missing comma after color");
	while (*l == ' ')
		l++;
	if (!ft_isdigit(*l))
		ft_throwerror("Missing color after comma");
	return (l);
}

int		ft_parse_color(char *l, t_all *all)
{
	char	*temp;
	char	c;
	int		r;
	int		g;
	int		b;

	temp = l;
	if (*l != 'F' && *l != 'C')
		return (0);
	c = *l;
	l += 2;
	if (!ft_isdigit(*l))
		ft_throwerror("Missing first color");
	r = ft_atoi(l);
	l = ft_skipdigitspace_comma(l);
	g = ft_atoi(l);
	l = ft_skipdigitspace_comma(l);
	b = ft_atoi(l);
	free(temp);
	if (c == 'F')
		return (ft_set_colors(r, g, b, &all->data.floor));
	return (ft_set_colors(r, g, b, &all->data.cell));
}

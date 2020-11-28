/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:46:11 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/30 20:47:39 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *a;

	if (lst == 0)
		return ;
	if (*lst != 0)
		a = *lst;
	else
	{
		*lst = new;
		return ;
	}
	while (a->next != 0)
		a = a->next;
	a->next = new;
}

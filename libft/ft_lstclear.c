/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:26:56 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 10:35:14 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;

	while (*lst != 0)
	{
		temp = *lst;
		*lst = (*lst)->next;
		del(temp->content);
		temp->next = 0;
		free(temp);
	}
	*lst = NULL;
}

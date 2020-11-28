/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:32:11 by hleilani          #+#    #+#             */
/*   Updated: 2020/10/31 11:03:14 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *temp;
	t_list *start_new;
	t_list *temp_new;

	(void)del;
	if ((start_new = ft_lstnew(f(lst->content))) == NULL)
		return (NULL);
	temp_new = start_new;
	while (lst != NULL)
	{
		if ((temp_new->next = ft_lstnew(f(lst->content))) == NULL)
			return (NULL);
		temp_new = temp_new->next;
		temp = lst;
		lst = lst->next;
	}
	temp_new->next = NULL;
	return (start_new);
}

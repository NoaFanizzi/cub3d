/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:32:05 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/27 12:33:27 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new || *lst == new)
		return ;
	if (*lst)
	{
		if (ft_lstlast(*lst) == new)
			new->prev->next = NULL;
		new->next = *lst;
		new->prev = NULL;
		(*lst)->prev = new;
		*lst = new;
		return ;
	}
	*lst = new;
	(*lst)->next = NULL;
	(*lst)->prev = NULL;
}

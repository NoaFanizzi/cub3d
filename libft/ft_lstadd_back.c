/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:04:52 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/29 12:41:20 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new || *lst == new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
	}
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
}

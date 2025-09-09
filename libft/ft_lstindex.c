/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:50:10 by lucas             #+#    #+#             */
/*   Updated: 2024/12/04 11:00:12 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstindex(t_list *lst, t_list *to_find)
{
	int		i;

	if (!lst || !to_find)
		return (-2);
	i = 0;
	while (lst)
	{
		if (lst == to_find)
			return (i);
		lst = lst->next;
		i++;
	}
	return (-1);
}

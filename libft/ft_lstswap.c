/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:44:39 by lucas             #+#    #+#             */
/*   Updated: 2024/11/27 12:29:23 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list *l1, t_list *l2)
{
	void	*tmp;

	if (!l1 || !l2 || l1 == l2)
		return ;
	tmp = l1->content;
	l1->content = l2->content;
	l2->content = tmp;
}

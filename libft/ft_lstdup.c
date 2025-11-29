/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:12:11 by lucas             #+#    #+#             */
/*   Updated: 2025/02/17 11:08:13 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(const t_list *lst, void (*del)(void*))
{
	t_list	*dup;
	t_list	*new;
	void	*new_content;

	if (!lst)
		return (NULL);
	dup = NULL;
	while (lst)
	{
		new_content = NULL;
		if (lst->content)
			new_content = malloc(sizeof(lst->content));
		ft_memcpy(new_content, lst->content, sizeof(lst->content));
		new = ft_lstnew(new_content);
		if (!new)
			return (free(new_content), ft_lstclear(&dup, del), NULL);
		ft_lstadd_back(&dup, new);
		lst = lst->next;
	}
	return (dup);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lmarcucc42lyon.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:34:42 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/19 11:18:02 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*tmp_content;
	t_list	*first;
	t_list	*new;

	first = NULL;
	if (!f || !del || !lst)
		return (NULL);
	while (lst)
	{
		tmp_content = f(lst->content);
		if (!tmp_content)
			return (ft_lstclear(&first, del), first);
		new = ft_lstnew(tmp_content);
		if (!new)
		{
			del(tmp_content);
			return (ft_lstclear(&first, del), first);
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:57:21 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/01/30 10:58:43 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_close_all(size_t nb, ...)
{
	va_list	args;
	size_t	i;

	va_start(args, nb);
	i = 0;
	while (i < nb)
	{
		close(va_arg(args, int));
		i++;
	}
	va_end(args);
}

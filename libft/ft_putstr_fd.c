/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:03:45 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/01/14 12:47:53 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	size_t	count;

	count = 0;
	if (!s)
	{
		count += write(fd, "(null)", 6);
	}
	else
		count += write(fd, s, ft_strlen(s));
	return (count);
}

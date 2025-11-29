/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:03:31 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/24 14:38:36 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	size_t	count;

	count = 0;
	count += ft_putstr_fd(s, fd);
	count += ft_putchar_fd('\n', fd);
	return (count);
}

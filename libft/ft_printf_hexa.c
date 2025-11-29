/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:00:07 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/01/29 16:38:37 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_putnbr_hex(long long int n, char *base, int fd)
{
	size_t	count;

	count = 0;
	if (n >= (long long int)ft_strlen(base))
	{
		count += ft_putnbr_hex(n / ft_strlen(base), base, fd);
		count += ft_putnbr_hex(n % ft_strlen(base), base, fd);
	}
	else
		count += ft_putchar_fd(base[n], fd);
	return (count);
}

size_t	ft_print_hexa(long long int nb, char param)
{
	if (param == 'x')
		return (ft_putnbr_hex(nb, "0123456789abcdef", 1));
	else if (param == 'X')
		return (ft_putnbr_hex(nb, "0123456789ABCDEF", 1));
	else
		return (ft_putnbr_hex(nb, "0123456789", 1));
}

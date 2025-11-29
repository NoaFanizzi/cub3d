/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:52:10 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/01/29 16:38:49 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_putnbr_pnt(unsigned long long int n, char *base, int fd)
{
	size_t	count;

	count = 0;
	if (n >= (unsigned long long int)ft_strlen(base))
	{
		count += ft_putnbr_pnt(n / ft_strlen(base), base, fd);
		count += ft_putnbr_pnt(n % ft_strlen(base), base, fd);
	}
	else
		count += ft_putchar_fd(base[n], fd);
	return (count);
}

size_t	ft_print_pnt(void *pnt)
{
	unsigned long long int	nb;
	size_t					count;

	count = 0;
	nb = (unsigned long long int)pnt;
	if (nb == 0)
	{
		count += ft_putstr_fd("(nil)", 1);
		return (count);
	}
	else
		count += ft_putstr_fd("0x", 1);
	count += ft_putnbr_pnt(nb, "0123456789abcdef", 1);
	return (count);
}

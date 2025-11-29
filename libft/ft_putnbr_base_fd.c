/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:54:15 by lucas             #+#    #+#             */
/*   Updated: 2024/12/06 22:13:30 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(long long int n, char *base, int fd)
{
	size_t			count;
	long long int	len;

	count = 0;
	len = (long long int)ft_strlen(base);
	if (n < 0)
	{
		n *= -1;
		count += ft_putchar_fd('-', fd);
	}
	if (n >= len)
	{
		count += ft_putnbr_base_fd(n / len, base, fd);
		count += ft_putnbr_base_fd(n % len, base, fd);
	}
	else
		count += ft_putchar_fd(base[n], fd);
	return (count);
}

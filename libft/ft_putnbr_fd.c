/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:56:42 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/24 21:30:38 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(long long int n, int fd)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count += ft_putchar_fd('-', fd);
	}
	if (n >= 10)
	{
		count += ft_putnbr_fd(n / 10, fd);
		count += ft_putnbr_fd(n % 10, fd);
	}
	else
		count += ft_putchar_fd(n + '0', fd);
	return (count);
}

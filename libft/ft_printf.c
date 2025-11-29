/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:33:52 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/01/29 16:41:49 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_print_pnt(void *pnt);
size_t	ft_print_hexa(long long int nb, char param);

static int	manage_format(char c, va_list arg)
{
	size_t	count;

	count = 0;
	if (c == '%')
		count += ft_putchar_fd('%', 1);
	else if (c == 'c')
		count += ft_putchar_fd(va_arg(arg, int), 1);
	else if (c == 's')
		count += ft_putstr_fd(va_arg(arg, char *), 1);
	else if (c == 'x' || c == 'X' || c == 'u')
		count += ft_print_hexa(va_arg(arg, unsigned int), c);
	else if (c == 'p')
		count += ft_print_pnt(va_arg(arg, void *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr_fd((long long int)va_arg(arg, int), 1);
	else if (c)
	{
		count += ft_putchar_fd('%', 1);
		count += ft_putchar_fd(c, 1);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	size_t	count;
	size_t	i;

	if (!format)
		return (0);
	va_start(arg, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += manage_format(format[i + 1], arg);
			i++;
			if (!format[i])
				return (va_end(arg), count);
		}
		else
			count += ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(arg);
	return (count);
}

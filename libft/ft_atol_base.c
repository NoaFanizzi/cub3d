/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:47:34 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/02/17 10:24:27 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(const char *base)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!ft_strlen(base))
		return (0);
	while (base[i])
	{
		if (ft_isspace(base[i]) || base[i] == '-' || base[i] == '+')
			return (0);
		j = 0;
		while (i && j < i)
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	in_base(char c, const char *base)
{
	size_t	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_nb(char c, const char *base)
{
	size_t	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

long int	ft_atol_base(const char *nptr, const char *base)
{
	long int		res;
	int				sign;
	size_t			i;

	if (!check_base(base))
		return (write(2, "ft_atol_base: non valid base\n", 30), 0);
	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (in_base(nptr[i], base))
	{
		res = res * ft_strlen(base) + get_nb(nptr[i], base);
		i++;
	}
	return (res * sign);
}

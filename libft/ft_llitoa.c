/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:56:07 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/24 15:09:12 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_num(long long int n)
{
	size_t	count;

	count = 0;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	count++;
	return (count);
}

char	*ft_llitoa(long long int n)
{
	size_t	i;
	size_t	is_neg;
	char	*res;

	if (ft_abs(n) == 0)
		return (ft_strdup("0"));
	is_neg = (n < 0);
	res = ft_calloc((count_num(ft_abs(n)) + is_neg + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (ft_abs(n) != 0)
	{
		res[i] = '0' + ft_abs(n % 10);
		n /= 10;
		i++;
	}
	if (is_neg)
		res[i] = '-';
	return (ft_strrev(res));
}

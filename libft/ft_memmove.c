/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lmarcucc42lyon.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:56:23 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/09 11:42:53 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d == s)
		return (dest);
	if (d < s || d >= s + n)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		s += n - 1;
		d += n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}

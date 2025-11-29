/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:55:38 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/02/17 10:27:24 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if ((nmemb * size) > __INT_MAX__)
		return (write(2, "ft_calloc: size > int_max\n", 27), NULL);
	if (size <= 0 || nmemb <= 0)
	{
		size = 0;
		nmemb = 0;
	}
	mem = malloc(nmemb * size);
	if (!mem)
		return (perror("ft_calloc: malloc"), NULL);
	ft_bzero(mem, (nmemb * size));
	return (mem);
}

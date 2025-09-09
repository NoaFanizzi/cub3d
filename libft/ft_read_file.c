/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:26:31 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/01/01 21:30:13 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_file(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*res;
	int		read_size;

	read_size = 1;
	res = NULL;
	while (read_size > 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
			return (ft_free(res), NULL);
		else if (read_size == 0)
			return (res);
		buffer[read_size] = '\0';
		res = ft_strjoin_free(res, buffer);
		if (!res)
			return (NULL);
	}
	return (res);
}

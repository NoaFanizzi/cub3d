/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:42:19 by lucas             #+#    #+#             */
/*   Updated: 2025/01/01 15:29:14 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hasline(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static void	get_rest(char *str)
{
	size_t	i;
	size_t	len;

	len = ft_hasline(str);
	if (!len)
		return (ft_bzero(str, (BUFFER_SIZE + 1) * sizeof(char)));
	i = 0;
	while (str[len + i])
	{
		str[i] = str[len + i];
		i++;
	}
	str[i] = 0;
}

static char	*crop_line(char *str)
{
	char	*res;
	size_t	length;
	size_t	i;

	if (!str)
		return (NULL);
	length = ft_hasline(str);
	if (!length)
		return (str);
	res = ft_calloc(length + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < length)
	{
		res[i] = str[i];
		i++;
	}
	return (free(str), res);
}

static char	*ft_read_fd(char *buffer, int fd)
{
	int		read_size;
	char	*res;

	res = NULL;
	if (ft_strlen(buffer) > 0)
	{
		res = ft_strdup(buffer);
		if (!res)
			return (NULL);
	}
	while (!ft_hasline(buffer))
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
		{
			if (res)
				free(res);
			return (NULL);
		}
		buffer[read_size] = 0;
		if (read_size == 0)
			return (res);
		res = ft_strjoin_free(res, buffer);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_bzero(buffer, sizeof(buffer)), NULL);
	line = ft_read_fd(buffer, fd);
	get_rest(buffer);
	line = crop_line(line);
	return (line);
}

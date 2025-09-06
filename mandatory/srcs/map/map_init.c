/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:02:30 by nofanizz          #+#    #+#             */
/*   Updated: 2025/09/06 15:04:59 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_size(t_size *size, char ***map)
{
	size->x = 0;
	while((*map)[size->x])
		size->x += 1;
}

void	get_tab_length(char ***tab, size_t *length)
{
	size_t	i;

	i = 0;
	*length = 0;
	while((*tab)[i])
	{
		*length += 1;
		i++;
	}
}

void	resize_map(char ***map, char ***new_map, char **temp)
{
	size_t	length;
	t_size	size;
	size_t	i;

	i = 0;
	get_map_size(&size, map);
	get_tab_length(map, &length);

	*new_map = ft_calloc(length + 2, sizeof(char *)); // + 1 pour la nouvelle lignet et + 1 pour le NULL de fin
	while(i < length)
	{
		(*new_map)[i] = ft_strdup((*map)[i]);
		i++;
	}
	(*new_map)[i] = ft_strdup(*temp);
	
}

int	update_map(char ***map, char **temp)
{
	char **new_map;
	char *trimmed_temp;
	
	trimmed_temp = ft_strtrim(*temp, "\n");
	ft_wipe(temp);
	if(*map)
	{
		resize_map(map, &new_map, &trimmed_temp);
	}
	else
	{
		new_map = ft_calloc(2, sizeof(char *));
		new_map[0] = ft_strdup(trimmed_temp);
	}
	if(*map)
		free_tab(map);
	*map = new_map;
	ft_wipe(&trimmed_temp);
	return(0);
}

char **get_map(char **argv)
{
	int fd;
	char *temp;
	char **map;
	
	map = NULL;
	fd = open(argv[1], O_RDONLY);
	while(1)
	{
		temp = get_next_line(fd);
		if(!temp)
			break;
		update_map(&map, &temp);
		free(temp);
	}
	return(map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_resizing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:43:18 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:45:26 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "parsing.h"

int	update_map(char ***map, char **temp)
{
	char	*trim;
	char	**new_map;

	if (!*temp)
		return (add_last_line(map), 0);
	if (!(*temp)[0])
		return (0);
	trim = ft_strtrim(*temp, "\n");
	if (!trim)
		return (1);
	if (*map)
	{
		if (resize_map(map, &new_map, &trim, 0))
			return (ft_wipe(&trim), 1);
		free_tab(map);
	}
	else if (init_first_lines(&new_map, trim))
		return (ft_wipe(&trim), 1);
	*map = new_map;
	ft_wipe(&trim);
	return (0);
}

static char	**copy_old_map(char **map, size_t len)
{
	char	**new_tab;
	size_t	i;

	new_tab = ft_calloc(len + 2, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_tab[i] = ft_strdup(map[i]);
		if (!new_tab[i])
		{
			while (i > 0)
				free(new_tab[--i]);
			free(new_tab);
			return (NULL);
		}
		i++;
	}
	return (new_tab);
}

int	resize_map(char ***map, char ***new_map, char **temp, int is_last)
{
	size_t	len;
	size_t	j;

	get_tab_length(map, &len);
	*new_map = copy_old_map(*map, len);
	if (!*new_map)
		return (1);
	(*new_map)[len] = ft_calloc(ft_strlen(*temp) + 3, sizeof(char));
	if (!(*new_map)[len])
	{
		free_tab(new_map);
		return (*new_map = NULL, 1);
	}
	(*new_map)[len][0] = 'X';
	j = 0;
	while ((*temp)[j] && !(is_last == 1 && !((*temp)[j + 1])))
	{
		(*new_map)[len][j + 1] = (*temp)[j];
		j++;
	}
	if (is_last == 0)
		(*new_map)[len][j + 1] = 'X';
	return (0);
}

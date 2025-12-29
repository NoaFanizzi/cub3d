/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 10:29:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/29 11:07:15 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "parsing.h"

int	check_validity(char **map)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((map[i][j] != '0' && map[i][j] != '1') && (map[i][j] != 'N'
					&& map[i][j] != 'S') && (map[i][j] != 'E'
					&& map[i][j] != 'W' && map[i][j] != 'X'))
				return (1);
			if ((map[i][j] == 'N' || map[i][j] == 'S') || (map[i][j] == 'E'
					|| map[i][j] == 'W'))
				count++;
			if (count > 1)
				return (1);
		}
	}
	if (count != 1)
		return (1);
	return (0);
}

int	check_border(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || j == 0 || ft_strlen(map[i - 1]) < j
					|| ft_strlen(map[i + 1]) < j || !map[i + 1] || !map[i][j
					+ 1])
					return (1);
				if (map[i][j - 1] == 'X' || map[i][j + 1] == 'X' || map[i
					- 1][j] == 'X' || map[i + 1][j] == 'X')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	map_parser(int argc, char **argv, char ***map, t_config *config)
{
	*map = NULL;
	if (argc != 2)
		return (1);
	if (is_suffix_correct(argv[1], "buc.") == 1)
		return (1);
	*map = get_map(argv, config);
	if (!*map)
		return (1);
	if (check_border(*map) == 1)
	{
		free_tab(map);
		clean_texture(config);
		return (1);
	}
	if (check_validity(*map) == 1)
	{
		free_tab(map);
		clean_texture(config);
		return (1);
	}
	replace_char(map, 'X', '1', config);
	return (0);
}

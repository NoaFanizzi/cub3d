/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:05:38 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/08 18:49:32 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_suffix_correct(char *str, char *suffix)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (str[i + 1])
		i++;
	while (j < 4)
	{
		if (str[i] != suffix[j])
			return (1);
		i--;
		j++;
	}
	return (0);
}

int	check_width(char **map)
{
	size_t	i;
	size_t	length;

	i = 1;
	length = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != length)
			return (1);
		i++;
	}
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
			if ((map[i][j] == '0') && (map[i][j - 1] == 'X' || map[i][j
					+ 1] == 'X' || map[i - 1][j] == 'X' || map[i
					+ 1][j] == 'X'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_validity(char **map)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] != '0' && map[i][j] != '1') && (map[i][j] != 'N'
					&& map[i][j] != 'S') && (map[i][j] != 'E'
					&& map[i][j] != 'W' && map[i][j] != 32))
				return (1);
			if ((map[i][j] == 'N' || map[i][j] == 'S') || (map[i][j] == 'E'
					|| map[i][j] == 'W'))
				count++;
			if (count > 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	map_parser(int argc, char **argv, char ***map, t_data *data)
{
	*map = NULL;
	if (argc != 2)
		return (1);
	if (is_suffix_correct(argv[1], "buc.") == 1)
		return (1);
	*map = get_map(argv, data);
	if(!*map)
		return(1);
	display_tab(*map);
	if (check_border(*map) == 1)
	{
		free_tab(map);
		return (1);
	}
	replace_char(map, 'X', '1');
	if (check_validity(*map) == 1)
	{
		free_tab(map);
		return (1);
	}
	ft_putstr_fd("\n\n\n", 1);
	display_tab(*map);
	return (0);
}

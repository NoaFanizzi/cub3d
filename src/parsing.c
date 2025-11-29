/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:58:49 by nofanizz          #+#    #+#             */
/*   Updated: 2025/11/29 20:10:14 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

int	parse_textures(int fd, t_config *config)
{
	char	*temp;

	temp = get_next_line(fd);
	while(is_only_space(temp) == 0)
	{
		free(temp);
		temp = get_next_line(fd);
	}
	if (!temp || check_and_add_texture(temp, "NO ", &config->tex_no))
		return (1);
	remove_last_char(config->tex_no);
	temp = get_next_line(fd);
	while(is_only_space(temp) == 0)
	{
		free(temp);
		temp = get_next_line(fd);
	}
	if (!temp || check_and_add_texture(temp, "SO ", &config->tex_so))
		return (1);
	remove_last_char(config->tex_so);
	temp = get_next_line(fd);
	while(is_only_space(temp) == 0)
	{
		free(temp);
		temp = get_next_line(fd);
	}
	if (!temp || check_and_add_texture(temp, "WE ", &config->tex_we))
		return (1);
	remove_last_char(config->tex_we);
	temp = get_next_line(fd);
	while(is_only_space(temp) == 0)
	{
		free(temp);
		temp = get_next_line(fd);
	}
	if (!temp || check_and_add_texture(temp, "EA ", &config->tex_ea))
		return (1);
	remove_last_char(config->tex_ea);
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

int	map_parser(int argc, char **argv, char ***map, t_config *config)
{
	*map = NULL;
	if (argc != 2)
		return (1);
	if (is_suffix_correct(argv[1], "buc.") == 1)
		return (1);
	*map = get_map(argv, config);
	if(!*map)
		return(1);
	//display_tab(*map);
	if (check_border(*map) == 1)
	{
		free_tab(map);
		return (1);
	}
	replace_char(map, 'X', '1', config);
	if (check_validity(*map) == 1)
	{
		free_tab(map);
		return (1);
	}
	ft_putstr_fd("\n\n\n", 1);
	//display_tab(*map);
	return (0);
}
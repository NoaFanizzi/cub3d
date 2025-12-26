/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:01:53 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/26 14:28:46 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	replace_char(char ***map, char old, char new, t_config *config)
{
	size_t	i;
	size_t	j;

	i = 0;
	(void)config;
	while ((*map)[i])
	{
		j = 0;
		while ((*map)[i][j])
		{
			if ((*map)[i][j] == old)
				(*map)[i][j] = new;
			j++;
		}
		i++;
	}
}

void	get_tab_length(char ***tab, size_t *length)
{
	size_t	i;

	i = 0;
	*length = 0;
	if (!(*tab))
		return ;
	while ((*tab)[i])
	{
		*length += 1;
		i++;
	}
}

int	resize_map(char ***map, char ***new_map, char **temp, int is_last)
{
	size_t	length;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	get_tab_length(map, &length);
	*new_map = ft_calloc(length + 2, sizeof(char *)); //PROTECTED
	if (!(*new_map))
		return (1);
	while (i < length)
	{
		(*new_map)[i] = ft_strdup((*map)[i]); //PROTECTED
		if (!(*new_map)[i])
		{
			while (i > 0)
				free((*new_map)[--i]);
			free(*new_map);
			*new_map = NULL;
			return (1);
		}
		i++;
	}
	length = ft_strlen(*temp);
	(*new_map)[i] = ft_calloc(length + 3, sizeof(char)); //PROTECTED
	if (!(*new_map)[i])
	{
		while (i > 0)
			free((*new_map)[--i]);
		free(*new_map);
		*new_map = NULL;
		return (1);
	}
	(*new_map)[i][0] = 'X';
	while ((*temp)[j])
	{
		if (is_last == 1 && !((*temp)[j + 1]))
			break ;
		(*new_map)[i][j + 1] = (*temp)[j];
		j++;
	}
	j++;
	if (is_last == 0)
		(*new_map)[i][j] = 'X';
	return(0);
}

void	load_delimitation_line(char **trimmed_map, size_t length)
{
	size_t	i;

	i = 0;
	(*trimmed_map)[0] = 'X';
	while (i < length)
	{
		(*trimmed_map)[i] = 'X';
		i++;
	}
}

void	add_last_line(char ***map)
{
	size_t	length;
	char	*line_full_x;
	char	**new_map;
	char	**old_map;

	length = get_last_line_length(map);
	line_full_x = ft_calloc(length + 1, sizeof(char));
	if (!line_full_x)
		return ;
	load_delimitation_line(&line_full_x, length);
	old_map = *map;
	if (resize_map(map, &new_map, &line_full_x, 1) == 0) // FIXED: Check return value
	{
		if (old_map)
			free_tab(&old_map);
		*map = new_map;
	}
	free(line_full_x);
}


int	update_map(char ***map, char **temp)
{
	char	**new_map;
	char	**old_map;
	char	*trimmed_line;
	char	*line_full_x;

	if (!*temp)
	{
		add_last_line(map);
		return (0);
	}
	if(!(*temp)[0])
		return(0);
	trimmed_line = ft_strtrim(*temp, "\n");
	if (!trimmed_line) // FIXED: Check for allocation failure
		return (1);
	if (*map)
	{
		old_map = *map;
		if (resize_map(map, &new_map, &trimmed_line, 0) != 0)
		{
			ft_wipe(&trimmed_line);
			return (1);
		}
		free_tab(&old_map);
	}
	else
	{
		line_full_x = ft_calloc(ft_strlen(trimmed_line) + 3, sizeof(char)); //PROTECTED
		if (!line_full_x)
		{
			ft_wipe(&trimmed_line);
			return (1);
		}
		load_delimitation_line(&line_full_x, ft_strlen(trimmed_line));
		if (resize_map(map, &new_map, &line_full_x, 0) != 0)
		{
			free(line_full_x);
			ft_wipe(&trimmed_line);
			return (1);
		}
		free(line_full_x);
		char **temp_map = new_map;
		if (resize_map(&temp_map, &new_map, &trimmed_line, 0) != 0)
		{
			free_tab(&temp_map);
			ft_wipe(&trimmed_line);
			return (1);
		}
		free_tab(&temp_map);
	}
	*map = new_map;
	ft_wipe(&trimmed_line);
	return (0);
}

int check_and_add_texture(char *temp, const char *prefix, char **dest)
{
    char *trimmed_path;

    if (ft_strncmp(temp, prefix, 3) != 0)
    {
        ft_wipe(&temp);
        return (1);
    }
    if (*dest) 
    {
        ft_putstr_fd("Error: Duplicate texture definition\n", 2);
        ft_wipe(&temp);
        return (1);
    }
    trimmed_path = ft_strtrim(&temp[3], " \t\n\v\f\r"); // PROTECTED
    ft_wipe(&temp);
    if (!trimmed_path || ft_strlen(trimmed_path) == 0)
    {
        if (trimmed_path) free(trimmed_path);
        return (1);
    }
    *dest = trimmed_path;
    return (0);
}

static int is_str_digit(char *str)
{
    int i = 0;

    while (str[i] && ft_isspace(str[i]))
        i++;
    if (!str[i])
        return (0);
    while (str[i] && ft_isdigit(str[i]))
        i++;
    while (str[i] && ft_isspace(str[i]))
        i++;
    if (str[i] != '\0')
        return (0);
    return (1);
}

int parse_color_line(char *line, char identifier, int *color_array)
{
    char    **colors;
    size_t  i;
    int     val;

    if (line[0] != identifier || !ft_isspace(line[1]))
        return (1);
    colors = ft_split(&line[2], ',');
    if (!colors)
        return (1);
    i = 0;
    while (colors[i])
        i++;
    if (i != 3)
    {
        free_tab((char ***)&colors);
        return (1);
    }
    i = 0;
    while (colors[i])
    {
        if (!is_str_digit(colors[i]))
        {
            free_tab((char ***)&colors);
            return (1);
        }
        val = ft_atoi(colors[i]);
        if (val < 0 || val > 255)
        {
            free_tab((char ***)&colors);
            return (1);
        }
        color_array[i] = val;
        i++;
    }
    free_tab((char ***)&colors);
    return (0);
}

int parse_colors(int fd, t_config *config)
{
	char	*temp;

	temp = get_next_line(fd); //PROTECTED
	while(is_only_space(temp) == 0)
	{
		ft_wipe(&temp);
		temp = get_next_line(fd);
	}
	printf("Color line 1: %s", temp);
	if (!temp || parse_color_line(temp, 'F', config->floor))
		return (1);
	temp = get_next_line(fd); //PROTECTED
	while(is_only_space(temp) == 0)
	{
		ft_wipe(&temp);
		temp = get_next_line(fd);
	}
	if (!temp || parse_color_line(temp, 'C', config->ceiling))
		return (1);
	return (0);
}

void	ft_display_colors(t_config *config)
{
	printf("Floor color: R=%d, G=%d, B=%d\n", config->floor[0], config->floor[1], config->floor[2]);
	printf("Ceiling color: R=%d, G=%d, B=%d\n", config->ceiling[0], config->ceiling[1], config->ceiling[2]);
}

/* map_init.c */

char    **get_map(char **argv, t_config *config)
{
    int     fd;
    char    *line;
    char    **map = NULL;
    int     map_started = 0;
    int     config_res;

    config->tex_no = NULL;
	config->tex_so = NULL; 
    config->tex_we = NULL;
	config->tex_ea = NULL;
	config->floor[0] = -1; 
    config->ceiling[0] = -1;

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) return (NULL);

    while ((line = get_next_line(fd)))
    {
        if (is_only_space(line) == 0)
        {
            free(line);
            if (map_started) // je check si y'a un ptn de trou
                map_started = 2;
            continue;
        }

        if (map_started == 2)
        {
            free(line);
            free_tab(&map);
            close(fd);
            return (NULL);
        }
        config_res = parse_config_line(line, config);
        if (config_res == 0) 
            free(line); 
        else if (config_res == 1)
        {
            free(line);
			free_tab(&map);
			close(fd);
			return (NULL);
        }
        else
        {
            if (!is_config_complete(config))
            {
                free(line);
				free_tab(&map);
				close(fd);
				return (NULL);
            }
            map_started = 1;
            if (update_map(&map, &line) != 0)
            {
                if (line)
					free(line);
                if (map)
				{
					free_tab(&map);
					close(fd);
					return (NULL);
				}
            }
            free(line);
        }
    }
    close(fd);
    if (!map || !is_config_complete(config)) 
        return (NULL);
    replace_char(&map, ' ', 'X', config);
    return (map);
}

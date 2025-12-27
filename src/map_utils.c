/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 10:10:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 10:11:56 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int is_str_digit(char *str)
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

int	validate_line_format(char *line, char identifier)
{
	if (line[0] != identifier || !ft_isspace(line[1]))
		return (1);
	return (0);
}
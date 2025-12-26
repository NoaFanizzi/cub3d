/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:45:38 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/26 14:29:13 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_last_line_pos(char ***map)
{
	size_t	i;

	i = 0;
	while ((*map)[i + 1])
		i++;
	return (i);
}

int	get_last_line_length(char ***map)
{
	size_t	pos;
	size_t	length;

	length = 0;
	pos = get_last_line_pos(map);
	length = ft_strlen((*map)[pos]);
	return (length);
}

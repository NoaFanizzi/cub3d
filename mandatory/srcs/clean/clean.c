/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 08:22:45 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 16:37:35 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"

void	free_tab(char ***tab)
{
	size_t	i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

void    wipe(char **str)
{
    free(*str);
    *str = NULL;
}

void    clean_texture(t_data *data)
{
    free(data->texture[NO].path);
	free(data->texture[SO].path);
	free(data->texture[EA].path);
	free(data->texture[WE].path);
}
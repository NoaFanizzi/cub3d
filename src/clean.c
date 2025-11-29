/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:04:23 by nofanizz          #+#    #+#             */
/*   Updated: 2025/11/29 16:23:56 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void remove_last_char(char *str)
{
    size_t i;

    if (!str)
        return;
    i = 0;
    while (str[i])
        i++;
    if (i > 0)
        str[i - 1] = '\0';
}

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

void    ft_wipe(char **str)
{
    free(*str);
    *str = NULL;
}

void    clean_texture(t_config *config)
{
    free(config->tex_no);
	free(config->tex_so);
	free(config->tex_ea);
	free(config->tex_we);
}

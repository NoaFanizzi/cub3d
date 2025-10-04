/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 08:22:45 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 08:51:35 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"

void    wipe(char **str)
{
    free(*str);
    *str = NULL;
}

void    clean_texture(t_texture *texture)
{
    free(texture->NO);
	free(texture->SO);
	free(texture->EA);
	free(texture->WE);
}
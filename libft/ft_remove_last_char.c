/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_last_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 10:55:01 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 10:56:10 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:52:17 by msalangi          #+#    #+#             */
/*   Updated: 2025/12/20 21:14:09 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	check_yellow(uint32_t color)
{
	uint8_t	r = (color >> 24) & 0xFF;
    uint8_t	g = (color >> 16) & 0xFF;
    uint8_t	b = (color >> 8) & 0xFF;

    if (r > 100 && g > 100 && b < 100)
		return (1);
	return (0);
}

// uint32_t	add_light(uint32_t color)
// {
// 	uint32_t	new_color;
	
// 	return ();
// }
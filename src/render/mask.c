/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:02:20 by msalangi          #+#    #+#             */
/*   Updated: 2025/12/17 23:00:22 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

float get_light_factor(float dist)
{
	return 1.0f / (1.0f + dist * dist * 0.1f);
}

uint32_t	apply_mask(uint32_t color, float light)
{	

	uint8_t a = (color >> 24) & 0xFF;
	uint8_t r = (color >> 16) & 0xFF;
	uint8_t g = (color >> 8) & 0xFF;
	uint8_t b = color & 0xFF;

	r = (uint8_t)(r * light);
	g = (uint8_t)(g * light);
	b = (uint8_t)(b * light);

    return (a << 24) | (r << 16) | (g << 8) | b;
}

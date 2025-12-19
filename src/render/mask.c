/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:02:20 by msalangi          #+#    #+#             */
/*   Updated: 2025/12/19 00:08:14 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

float	vignette_factor(int x, int y, int w, int h, float radius)
{
    float	nx = (2.0f * x) / (float)w - 1.0f;
    float	ny = (2.0f * y) / (float)h - 1.0f;
    float	d = sqrtf(nx * nx + ny * ny);
    const float maxd = 1.41421356f;
    float	t;

    t = (d - radius) / (maxd - radius);
    if (t <= 0.0f)
        return 1.0f;
    if (t >= 1.0f)
        return 0.0f;
    t = t * t * (3.0f - 2.0f * t);
    return 1.0f - t;
}

float get_light_factor(float dist)
{
	if (dist < 0.0f)
        dist = 0.0f;
    return 1.0f / (1.0f + dist * 0.11f);
}

uint32_t	apply_mask(uint32_t color, float light, float fl)
{	
	if (light < 0.0f)
        light = 0.0f;
    if (light > 1.0f)
        light = 1.0f;

    uint8_t	r = (color >> 24) & 0xFF;
    uint8_t	g = (color >> 16) & 0xFF;
    uint8_t	b = (color >> 8) & 0xFF;
    uint8_t	a = color & 0xFF;

    r = (uint8_t)fminf(255.0f, r * light * fl);
    g = (uint8_t)fminf(255.0f, g * light * fl);
    b = (uint8_t)fminf(255.0f, b * light * fl);

    return ((uint32_t)r << 24) | ((uint32_t)g << 16)
        | ((uint32_t)b << 8) | (uint32_t)a;
}

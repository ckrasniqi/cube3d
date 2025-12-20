/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:02:20 by msalangi          #+#    #+#             */
/*   Updated: 2025/12/20 23:43:12 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

float	vignette_factor(int x, int y, t_settings *cfg, float radius)
{
	float	nx;
	float	ny;
	float	t;

	nx = (2.0f * x) / (float)cfg->width - 1.0f;
	ny = (2.0f * y) / (float)cfg->height - 1.0f;
	t = (sqrtf(nx * nx + ny * ny) - radius) / (1.41421356f - radius);
	if (t <= 0.0f)
		return (1.0f);
	if (t >= 1.0f)
		return (0.0f);
	t = t * t * (3.0f - 2.0f * t);
	return (1.0f - t);
}

float	get_light_factor(float dist)
{
	if (dist < 0.0f)
		dist = 0.0f;
	return (1.0f / (1.0f + dist * 0.15f));
}

uint32_t	apply_mask(uint32_t color, float light, float fl)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (light < 0.0f)
		light = 0.0f;
	if (light > 1.0f)
		light = 1.0f;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	r = (uint8_t)fminf(255.0f, r * light * fl);
	g = (uint8_t)fminf(255.0f, g * light * fl);
	b = (uint8_t)fminf(255.0f, b * light * fl);
	return (((uint32_t)r << 24) | ((uint32_t)g << 16)
		| ((uint32_t)b << 8) | (uint32_t)a);
}

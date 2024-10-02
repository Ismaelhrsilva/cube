/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:23:13 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/02 16:39:18 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <math.h>

float	pytheorem(float a, float b)
{
	return (sqrt((a * a) + (b * b)));
}

int	horizontal_unit_circle(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int	vertical_unit_circle(float angle)
{
	return (angle > M_PI * 0.5 && angle < M_PI * 1.5);
}

float	normalize(float angle)
{
	float	limit;

	limit = M_PI * 2;
	return (angle - (limit * ((int)(angle / limit))));
}

uint32_t	reverse_bytes(unsigned int c)
{
	return ((c & R) >> 8 | (c & G) << 8 | (c & B) << 24 | (c & A) >> 24);
}

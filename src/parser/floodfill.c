/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:52:56 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/16 20:23:09 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "parser.h"
#include <stdint.h>
#include <stdlib.h>

static void	push(t_map *map, t_point **stack, int32_t x, int32_t y)
{
	t_point	*point;

	if (!stack)
		return ;
	point = (t_point *) malloc(sizeof(t_point));
	if (!point)
		panic(map, ft_strdup("Failed to allocate memory"), 1);
	point->x = x;
	point->y = y;
	point->next = *stack;
	*stack = point;
}

static t_point	*pop(t_point **stack)
{
	t_point	*p;

	if (!stack || !*stack)
		return (NULL);
	p = *stack;
	*stack = p->next;
	return (p);
}

static void	clear(t_point **stack)
{
	t_point	*p;

	if (!stack)
		return ;
	while (*stack)
	{
		p = *stack;
		*stack = p->next;
		free(p);
	}
	return ;
}

void	floodfill(t_map *map, int32_t x, int32_t y)
{
	t_point	*stack;
	t_point	*p;

	stack = NULL;
	push(map, &stack, x, y);
	while (stack)
	{
		p = pop(&stack);
		if (p->x < 0 || p->y < 0 || p->x >= map->width || p->y >= map->height
			|| map->map[p->y][p->x] == ' ')
		{
			free(p);
			clear(&stack);
			panic(map, ft_strdup("Floodfill error"), 1);
		}
		if (!ft_strchr("12", map->map[p->y][p->x]))
		{
			map->map[p->y][p->x] = '2';
			push(map, &stack, p->x + 1, p->y);
			push(map, &stack, p->x, p->y + 1);
			push(map, &stack, p->x - 1, p->y);
			push(map, &stack, p->x, p->y - 1);
		}
		free(p);
	}
}

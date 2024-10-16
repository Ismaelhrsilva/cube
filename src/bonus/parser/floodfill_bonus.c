/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:52:56 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/16 20:29:48 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
#include "libft.h"
#include "parser_bonus.h"
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

static void	validate_character(t_map *map, t_point *stack, t_point *p)
{
	const int32_t		x = p->x;
	const int32_t		y = p->y;
	const unsigned char	c[9] = {
		map->map[y - 1][x - 1], map->map[y - 1][x], map->map[y - 1][x + 1],
		map->map[y][x - 1], map->map[y][x], map->map[y][x +1],
		map->map[y + 1][x - 1], map->map[y + 1][x], map->map[y + 1][x + 1]};

	if (c[4] != 'D')
	{
		map->map[y][x] = '2';
		return ;
	}
	if ((c[1] == 'D' || c[3] == 'D' || c[5] == 'D' || c[7] == 'D')
		|| ((c[1] == '1' && c[3] == '1') || (c[1] == '1' && c[5] == '1')
			|| (c[3] == '1' && c[7] == '1') || (c[5] == '1' && c[7] == '1'))
		|| ((c[1] == '1' && c[7] != '1') || (c[7] == '1' && c[1] != '1')
			|| (c[3] == '1' && c[5] != '1') || (c[5] == '1' && c[3] != '1'))
		|| (c[1] != '1' && c[3] != '1' && c[5] != '1' && c[7] != '1'))
	{
		free(p);
		clear(&stack);
		panic(map, ft_strdup("Invalid door"), 1);
	}
	map->map[y][x] = 'd';
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
		if (!ft_strchr("12d", map->map[p->y][p->x]))
		{
			validate_character(map, stack, p);
			push(map, &stack, p->x + 1, p->y);
			push(map, &stack, p->x, p->y + 1);
			push(map, &stack, p->x - 1, p->y);
			push(map, &stack, p->x, p->y - 1);
		}
		free(p);
	}
}

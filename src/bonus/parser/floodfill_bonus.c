/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:52:56 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/12 12:16:45 by rde-mour         ###   ########.org.br   */
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

static bool	clear(t_point **stack, bool status)
{
	t_point	*p;

	if (!stack)
		return (status);
	while (*stack)
	{
		p = *stack;
		*stack = p->next;
		free(p);
	}
	return (status);
}

static void	validate_character(t_map *map, int32_t x, int32_t y)
{
	const unsigned char	c[9] = {
		map->map[y - 1][x - 1], map->map[y - 1][x], map->map[y - 1][x + 1],
		map->map[y][x - 1], map->map[y][x], map->map[y][x +1],
		map->map[y + 1][x - 1], map->map[y + 1][x], map->map[y + 1][x + 1]
	};

	if (c[4] == 'D')
	{
		if (c[1] == 'D' || c[3] == 'D' || c[5] == 'D' || c[7] == 'D')
			panic(map, ft_strdup("Two doors side by side"), 1);
		if ((c[1] == '1' && c[3] == '1') || (c[1] == '1' && c[5] == '1')
			|| (c[3] == '1' && c[7] == '1') || (c[5] == '1' && c[7] == '1'))
			panic(map, ft_strdup("Invalid corner door"), 1);
		if ((c[1] == '1' && c[7] != '1') || (c[7] == '1' && c[1] != '1')
			|| (c[3] == '1' && c[5] != '1') || (c[5] == '1' && c[3] != '1'))
			panic(map, ft_strdup("Invalid wall door"), 1);
		if (c[1] != '1' && c[3] != '1' && c[5] != '1' && c[7] != '1')
			panic(map, ft_strdup("Invalid loose door"), 1);
		map->map[y][x] = 'd';
	}
	else
		map->map[y][x] = '2';
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
		if (p->x < 0 || p->y < 0 || p->x >= map->width || p->y >= map->height)
		{
			free(p);
			clear(&stack, false);
			panic(map, ft_strdup("Floodfill error"), 1);
		}
		if (!ft_strchr("12d", map->map[p->y][p->x]))
		{
			validate_character(map, p->x, p->y);
			push(map, &stack, p->x + 1, p->y);
			push(map, &stack, p->x, p->y + 1);
			push(map, &stack, p->x - 1, p->y);
			push(map, &stack, p->x, p->y - 1);
		}
		free(p);
	}
}

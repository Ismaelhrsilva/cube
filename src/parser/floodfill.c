/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:52:56 by rde-mour          #+#    #+#             */
/*   Updated: 2024/09/30 20:10:09 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static void	push(t_point **stack, int32_t x, int32_t y)
{
	t_point	*point;

	if (!stack)
		return ;
	point = (t_point *) malloc(sizeof(t_point));
	if (!point)
		exit(1);
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
}

_Bool	floodfill(t_map *map, int32_t x, int32_t y)
{
	t_point	*stack;
	t_point	*p;

	stack = NULL;
	push(&stack, x, y);
	while (stack)
	{
		p = pop(&stack);
		if (p->x < 0 || p->y < 0 || p->x > map->width || p->y > map->height)
		{
			clear(&stack);
			return (false);
		}
		if (!ft_strchr("12d", map->map[p->y][p->x]))
		{
			if (map->map[p->y][p->x] != 'D')
				map->map[p->y][p->x] = '2';
			else
				map->map[p->y][p->x] = 'd';
			push(&stack, p->x + 1, p->y);
			push(&stack, p->x, p->y + 1);
			push(&stack, p->x - 1, p->y);
			push(&stack, p->x, p->y - 1);
		}
		free(p);
	}
	return (true);
}

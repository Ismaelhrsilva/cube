/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:26:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/09/28 12:20:00 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cube.h"
# include <stdint.h>
# define MEMORY_SIZE 64

typedef struct s_point {
	int32_t			x;
	int32_t			y;
	struct s_point	*next;
}	t_point;

_Bool	floodfill(t_map *map, int32_t x, int32_t y);
void	get_map(char *path, t_map *map);
void	panic(t_map *map, char *str, char *message, uint32_t error);
_Bool	validate_file(char *path);
_Bool	validate_map(t_map	*map);
_Bool	validate_floodfill(t_map *map);
void	print(t_map *map);

#endif

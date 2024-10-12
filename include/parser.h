/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:26:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/07 16:14:59 by rde-mour         ###   ########.org.br   */
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

void	floodfill(t_map *map, int32_t x, int32_t y);
void	get_map(char *path, t_map *map);
void	panic(t_map *map, char *message, uint8_t error);
void	validate_file(char *path);
void	validate_map(t_map	*map);
void	validate_floodfill(t_map *map);
void	print(t_map *map);

#endif

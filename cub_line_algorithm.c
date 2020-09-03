/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_line_algorithm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 12:08:00 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/03 13:10:17 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_linecoords	coords_init(int x0, int y0, int x1, int y1)
{
	t_linecoords	coords;

	coords.x0 = x0;
	coords.y0 = y0;
	coords.x1 = x1;
	coords.y1 = y1;
	return (coords);
}

void			dda_line_algorithm(t_imgdata *img, t_linecoords coords,
					int colour)
{
	int		i;
	t_dda	line;

	line.dx = coords.x1 - coords.x0;
	line.dy = coords.y1 - coords.y0;
	line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy);
	line.xinc = line.dx / (float)line.steps;
	line.yinc = line.dy / (float)line.steps;
	line.x = coords.x0;
	line.y = coords.y0;
	i = 0;
	while (i <= line.steps)
	{
		my_mlx_pixel_put(img, line.x, line.y, colour);
		line.x += line.xinc;
		line.y += line.yinc;
		i++;
	}
}

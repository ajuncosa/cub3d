/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 12:08:00 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/30 11:32:11 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_imgdata *data, int x, int y, int color)
{
    char    *dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

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

void			draw_square(t_vars *vars, t_sprite *sprite, t_linecoords coords, int colour)
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;

	x0 = coords.x0;
	while (x0 < 0)
		x0++;
	x1 = coords.x1;
	y0 = coords.y0;
	y1 = coords.y1;
	while (x0 <= x1)
	{
		coords = coords_init(x0, y0, x0, y1);
		if (vars->wall.dist[x0] > sprite->dist)
			dda_line_algorithm(&vars->img, coords, colour);
		x0++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:40:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/26 17:12:29 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_sprite_info(t_vars *vars, t_sprite *sprite)
{
	float			xinc;
	float			yinc;
	float			pixels_per_degree;

	xinc = (sprite->map_x - vars->player.x);
	yinc = (sprite->map_y - vars->player.y);
	sprite->dist = sqrt(pow(xinc, 2) + pow(yinc, 2));
	sprite->angle = atan2(yinc, xinc) * 180 / M_PI;
	sprite->angle += (sprite->angle < 0) ? 360 : 0;
	sprite->draw_height = (int)((vars->window.height / 2) / sprite->dist);
	sprite->rel_angle = sprite->angle - vars->ray.angle0;
	if (sprite->rel_angle > 0 || sprite->rel_angle < -30)
		sprite->rel_angle += (sprite->rel_angle < 0) ? 360 : 0;
	pixels_per_degree = vars->window.width / vars->player.fov;
	sprite->screen_x = pixels_per_degree * sprite->rel_angle;
	sprite->screen_y = vars->window.height / 2;
	sprite->draw_width = (sprite->vars.width *
		sprite->draw_height / sprite->vars.height);
	sprite->y_inc = (sprite->draw_height * 2) / sprite->vars.height;
	sprite->x_inc = (sprite->draw_width * 2) / sprite->vars.width;
}

void	sort_sprite_array(t_vars *vars)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < vars->sprite_count)
	{
		j = 0;
		while (j < vars->sprite_count)
		{
			if (vars->sprite[j].dist < vars->sprite[i].dist)
			{
				tmp = vars->sprite[j];
				vars->sprite[j] = vars->sprite[i];
				vars->sprite[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	square_sprite(t_vars *vars, t_sprite *sprite,
					t_linecoords coords, int colour)
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
			dda_line_algorithm(vars, coords, colour);
		x0++;
	}
}

void	paint_sprite(t_vars *vars, t_sprite *sprite)
{
	float			x;
	float			y;
	unsigned int	col;
	t_linecoords	coords;
	int				i;

	x = sprite->screen_x - sprite->draw_width;
	sprite->vars.position_x = 0;
	if (x < -1000 || x > vars->window.width)
		return ;
	while (sprite->vars.position_x < sprite->vars.width)
	{
		y = sprite->screen_y - sprite->draw_height;
		i = -1;
		while (++i < sprite->vars.height)
		{
			coords = coords_init(x, y, x + sprite->x_inc, y + sprite->y_inc);
			col = ((unsigned int *)sprite->vars.img.addr)
					[i * sprite->vars.width + sprite->vars.position_x];
			(col != 0x000000) ? square_sprite(vars, sprite, coords, col) : 0;
			y += sprite->y_inc;
		}
		sprite->vars.position_x++;
		x += sprite->x_inc;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:40:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/09 14:39:40 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	paint_sprite(t_vars *vars, t_sprite *sprite)
{
	float			x;
	float			y;
	unsigned int	col;
	t_linecoords	coords;
	int				i;

	sprite->y_inc = (sprite->draw_height * 2) / sprite->vars.height;
	sprite->x_inc = (sprite->draw_width * 2) / sprite->vars.width;
	x = sprite->screen_x - sprite->draw_width;
	sprite->vars.position_x = 0;
	while (sprite->vars.position_x < sprite->vars.width)
	{
		y = sprite->screen_y - sprite->draw_height;
		i = -1;
		while (++i < sprite->vars.height)
		{
			coords = coords_init(x, y, x + sprite->x_inc, y + sprite->y_inc);
			col = ((unsigned int *)sprite->vars.img.addr)
					[i * sprite->vars.width + sprite->vars.position_x];
			(col != 0x000000) ? draw_square(vars, sprite, coords, col) : 0;
			y += sprite->y_inc;
		}
		sprite->vars.position_x++;
		x += sprite->x_inc;
	}
}

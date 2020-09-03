/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:40:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/03 13:24:48 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite(t_vars *vars, t_sprite *sprite, int x)
{
	float			y_incrementer;
	float			y;
	int				i;
	unsigned int	colour;
	t_linecoords	coords;

	y_incrementer = (sprite->draw_height * 2) / sprite->vars.height;
	y = SCREEN_HEIGHT / 2 - sprite->draw_height;
	i = 0;
	
	while (i < sprite->vars.height)
	{
		coords = coords_init(x, y, x, y + y_incrementer);
		colour = ((unsigned int *)sprite->vars.img.addr)
			[i * sprite->vars.width + sprite->vars.position_x];
		if (colour != 0x000000)
			dda_line_algorithm(&vars->img, coords, colour);
		y += y_incrementer;
		i++;
	}
}

void	sprite_raycasting(t_vars *vars, t_sprite *sprite, int x)
{
	float	x_square;
	float	y_square;

	x_square = pow(vars->player.x - sprite->ray_x, 2);
	y_square = pow(vars->player.y - sprite->ray_y, 2);
	sprite->dist = sqrt(x_square + y_square);
	sprite->dist = sprite->dist * cos((vars->ray.angle -
		vars->player.angle) * M_PI / 180);
	sprite->draw_height = (int)((SCREEN_HEIGHT / 2) / sprite->dist);
	sprite->vars.position_x = (int)fmod(sprite->vars.width *
		(sprite->ray_x + sprite->ray_y), sprite->vars.width);
	draw_sprite(vars, sprite, x);
}

void	paint_sprite(t_vars *vars, t_sprite *sprite, int x)
{
	int	sprite_hit;

	sprite_hit = 0;
	sprite->ray_x = vars->player.x;
	sprite->ray_y = vars->player.y;
	while (sprite_hit != 2 && sprite_hit != 1)
	{
		sprite->ray_x += vars->ray.cos;
		sprite_hit = map[(int)sprite->ray_y][(int)sprite->ray_x];
		if (sprite_hit == 2)
		{
			sprite_raycasting(vars, sprite, x);
			break ;
		}
		sprite->ray_y += vars->ray.sin;
		sprite_hit = map[(int)sprite->ray_y][(int)sprite->ray_x];
		if (sprite_hit == 2)
		{
			sprite_raycasting(vars, sprite, x);
			break ;
		}
	}
}

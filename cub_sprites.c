/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:40:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/07 13:45:46 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
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
*/
void	paint_sprite(t_vars *vars, t_sprite *sprite, int x)
{
	t_linecoords	coords;

	sprite->ray_x = (floor(sprite->ray_x) + 0.5);
	sprite->ray_y = (floor(sprite->ray_y) + 0.5);
	sprite->dist_x = sprite->ray_x - vars->player.x;
	sprite->dist_y = sprite->ray_y - vars->player.y;
	sprite->dist = sqrt(pow(sprite->dist_x, 2) + pow(sprite->dist_y, 2));
	sprite->draw_height = (int)((SCREEN_HEIGHT / 2) / sprite->dist);
	sprite->angle = (atan(sprite->sin / sprite->cos) * M_PI) / 180;
	printf("atan: %f\n", sprite->angle);
	if ((vars->player.angle - vars->player.halffov) < 0)
		sprite->angle_zero = 360 + (vars->player.angle - vars->player.halffov);
	else
		sprite->angle_zero = vars->player.angle - vars->player.halffov;
	sprite->angle = sprite->angle_zero - sprite->angle;
	
	float pixels_per_degree = SCREEN_WIDTH / vars->player.fov;
	sprite->screen_x = pixels_per_degree * sprite->angle;
	sprite->screen_y = SCREEN_HEIGHT / 2;
	sprite->draw_width = (sprite->vars.width * sprite->draw_height) / sprite->vars.height;
	printf("primer angulo del fov: %f\nspriteang: %f\npixelspdeg: %f\nx: %f\ny: %f\n", sprite->angle_zero, sprite->angle, pixels_per_degree, sprite->screen_x, sprite->screen_y);
	coords = coords_init(sprite->screen_x - sprite->draw_width / 2, sprite->screen_y - sprite->draw_height / 2, sprite->screen_x + sprite->draw_width / 2, sprite->screen_y + sprite->draw_height / 2);
	dda_line_algorithm(&vars->img, coords, 0xFF0000);
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:40:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/17 13:35:47 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_found_fill_vars(t_vars *vars, t_sprite *sprite)
{
	if (sprite->found == 0)
	{
		sprite->map_x = (int)sprite->ray_x;
		sprite->map_y = (int)sprite->ray_y;
		sprite->angle1 = vars->ray.angle;
		sprite->found = 1;
	}
	else
		sprite->angle2 = vars->ray.angle;
}

void	find_sprite(t_vars *vars, t_sprite *sprite)
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
			printf("%d, %d\n", (int)sprite->ray_x, (int)sprite->ray_y);
			sprite_found_fill_vars(vars, sprite);
			break ;
		}
		sprite->ray_y += vars->ray.sin;
		sprite_hit = map[(int)sprite->ray_y][(int)sprite->ray_x];
		if (sprite_hit == 2)
		{
			printf("%d, %d\n", (int)sprite->ray_x, (int)sprite->ray_y);
			sprite_found_fill_vars(vars, sprite);
			break ;
		}
	}
}

void	paint_sprite(t_vars *vars, t_sprite *sprite)
{
	t_linecoords	coords;
	float			y_incrementer;
	float			x_incrementer;
	float			y;
	float			x;
	int				i;
	unsigned int	colour;

	sprite->map_x = (floor(sprite->map_x) + 0.5);
	sprite->map_y = (floor(sprite->map_y) + 0.5);
	sprite->dist = sqrt(pow(sprite->map_x - vars->player.x, 2) + pow(sprite->map_y - vars->player.y, 2));
	sprite->draw_height = (int)((SCREEN_HEIGHT / 2) / sprite->dist); // altura de la mitad del dibujo del sprite
	if ((vars->player.angle - vars->player.halffov) < 0)
 		sprite->angle0 = 360 + (vars->player.angle - vars->player.halffov);
 	else
 		sprite->angle0 = vars->player.angle - vars->player.halffov;
	sprite->angle1 -= sprite->angle0;
	sprite->angle2 -= sprite->angle0;
	sprite->angle = (sprite->angle2 + sprite->angle1) / 2; //este es el ángulo relativo del sprite sobre el FOV (hago la media para coger el central. Si cogiese el ángulo total en vez del relativo la screen_x quedaría súper grande)
	//printf("ang 1: %f\nang 2: %f\nang 0: %f\n", sprite->angle1, sprite->angle2, sprite->angle0);
	float pixels_per_degree = SCREEN_WIDTH / vars->player.fov;
	sprite->screen_x = pixels_per_degree * sprite->angle; // me da la x central de donde se va a dibujar el sprite
	//printf("screen x: %f\n\n", sprite->screen_x);
	sprite->screen_y = SCREEN_HEIGHT / 2;
	sprite->draw_width = (sprite->vars.width * sprite->draw_height) / sprite->vars.height; // regla de tres
	y_incrementer = (sprite->draw_height * 2) / sprite->vars.height;
	x_incrementer = (sprite->draw_width * 2) / sprite->vars.width;
	x = sprite->screen_x - sprite->draw_width;
	sprite->vars.position_x = 0;
	while (sprite->vars.position_x <= sprite->vars.width)
	{
		y = sprite->screen_y - sprite->draw_height;
		i = 0;
		while (i < sprite->vars.height)
		{
			coords = coords_init(x, y, x + x_incrementer, y + y_incrementer);
			colour = ((unsigned int *)sprite->vars.img.addr)[i * sprite->vars.width + sprite->vars.position_x];
			if (colour != 0x000000)
				draw_square(&vars->img, coords, colour);
			y += y_incrementer;
			i++;
		}
		sprite->vars.position_x++;
		x += x_incrementer;
	}
}

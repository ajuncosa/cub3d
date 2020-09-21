/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:40:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/21 13:28:38 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_found_fill_vars(t_vars *vars, float ray_x, float ray_y)
{
	int			count;
	t_sprite	*sprite;

	count = 0;
	sprite = vars->sprite;
	while (count < vars->sprite_count)
	{
		if (sprite[count].array_x == (int)ray_x && sprite[count].array_y == (int)ray_y)
			break ;
		count++;
	}
	if (sprite[count].found == 0)
	{
		sprite[count].map_x = (int)ray_x + 0.5;
		sprite[count].map_y = (int)ray_y + 0.5;
		sprite[count].angle1 = vars->ray.angle;
		sprite[count].found = 1;
	}
	else
		sprite[count].angle2 = vars->ray.angle;
}

void	find_sprite(t_vars *vars)
{
	int		sprite_hit;
	float	ray_x;
	float	ray_y;

	sprite_hit = 0;
	ray_x = vars->player.x;
	ray_y = vars->player.y;
	while (sprite_hit != 2 && sprite_hit != 1)
	{
		ray_x += vars->ray.cos;
		sprite_hit = map[(int)ray_y][(int)ray_x];
		if (sprite_hit == 2)
		{
		//	printf("%d, %d\n", (int)ray_x, (int)ray_y);
			sprite_found_fill_vars(vars, ray_x, ray_y);
			break ;
		}
		ray_y += vars->ray.sin;
		sprite_hit = map[(int)ray_y][(int)ray_x];
		if (sprite_hit == 2)
		{
		//	printf("%d, %d\n", (int)ray_x, (int)ray_y);
			sprite_found_fill_vars(vars, ray_x, ray_y);
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
	printf("%d\n", sprite->vars.width);
	printf("%d\n", sprite->vars.position_x);
	while (sprite->vars.position_x <= sprite->vars.width)
	{
		printf("hola\n");
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

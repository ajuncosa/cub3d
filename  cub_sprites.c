/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:40:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/14 13:08:41 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_sprite(t_vars *vars, t_sprite *sprite)
{
	t_linecoords	coords;
	float			y_incrementer;
	float			x_incrementer;
	float			y;
	float			x;
	int				i;
	int				j;
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
	printf("angle0: %f\nangle: %f\nangle1: %f\nangle2: %f\n\n", sprite->angle0, sprite->angle, sprite->angle1, sprite->angle2);
	float pixels_per_degree = SCREEN_WIDTH / vars->player.fov;
	sprite->screen_x = pixels_per_degree * sprite->angle; // me da la x central de donde se va a dibujar el sprite
	//printf("sprite->screen_x: %f\n", sprite->screen_x);
	sprite->screen_y = SCREEN_HEIGHT / 2;
	//printf("sprite->screen_y: %f\n", sprite->screen_y);
	sprite->draw_width = (int)((sprite->vars.width * sprite->draw_height) / sprite->vars.height); // regla de tres
	//printf("draw_width: %f\nheight: %f\n", sprite->draw_width, sprite->draw_height);
	//printf("primer angulo del fov: %f\npixelspdeg: %f\nx: %f\ny: %f\n\n", sprite->angle0, pixels_per_degree, sprite->screen_x, sprite->screen_y);

	
	y_incrementer = (sprite->draw_height * 2) / sprite->vars.height;
	x_incrementer = (sprite->draw_width * 2) / sprite->vars.width;
	//printf("yinc: %f, xinc: %f\n", y_incrementer, x_incrementer);
	x = sprite->screen_x - sprite->draw_width;
	sprite->vars.position_x = 0;
	while (sprite->vars.position_x < sprite->vars.width)
	{
		j = 0; // la j es un int y el x_incrementer es un float; a lo mejor se soluciona si hago un draw_square?
		while (j < x_incrementer && x < sprite->screen_x + sprite->draw_width)
		{
			i = 0;
			y = sprite->screen_y - sprite->draw_height;
			while (i < sprite->vars.height)
			{
				coords = coords_init(x, y, x, y + y_incrementer);
				colour = ((unsigned int *)sprite->vars.img.addr)[i * sprite->vars.width + sprite->vars.position_x];
				dda_line_algorithm(&vars->img, coords, colour);
				y += y_incrementer;
				i++;
			}
			j++;
			x++;
		}
		//x += x_incrementer;
		sprite->vars.position_x++;
	
	}
		printf("sprite pos x: %d\n\n", sprite->vars.position_x);
}

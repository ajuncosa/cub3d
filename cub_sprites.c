/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:40:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/15 12:15:13 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_sprites(t_vars *vars)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	vars->sprite_count = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (vars->map.map[i][j] != '0' && vars->map.map[i][j] != '1'
				&& vars->map.map[i][j] != '9' && vars->map.map[i][j] != ' ')
				vars->sprite_count++;
			j++;
		}
		i++;
	}
}

int		init_sprite_array(t_vars *vars)
{
	int i;
	int j;
	int	count;

	count_sprites(vars);
	if (vars->sprite_count == 0)
		return (1);
	if (!(vars->sprite = malloc(vars->sprite_count * sizeof(t_sprite))))
		return (0);
	i = 0;
	count = 0;
	while (i < vars->map.height)
	{
		j = -1;
		while (++j < vars->map.width)
		{
			if (vars->map.map[i][j] != '0' && vars->map.map[i][j] != '1'
				&& vars->map.map[i][j] != '9' && vars->map.map[i][j] != ' ')
			{
				vars->sprite[count].map_x = j + 0.5;
				vars->sprite[count].map_y = i + 0.5;
				//vars->sprite[count].id = map[i][j];
				count++;
			}
		}
		i++;
	}
	return (!(vars->wall.dist = malloc(vars->window.width * sizeof(float))) ? 0 : 1);
}

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
	if (sprite->rel_angle > 0 || sprite->rel_angle < -30) // para poder usar los negativos cercanos al limite izq de la pantalla al calcular la screen_x
		sprite->rel_angle += (sprite->rel_angle < 0) ? 360 : 0;
	pixels_per_degree = vars->window.width / vars->player.fov;
	sprite->screen_x = pixels_per_degree * sprite->rel_angle;
	sprite->screen_y = vars->window.height / 2;
	sprite->draw_width = (sprite->vars.width * sprite->draw_height / sprite->vars.height);
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
	unsigned int	colour;
	t_linecoords	coords;
	int				i;

	sprite->y_incrementer = (sprite->draw_height * 2) / sprite->vars.height;
	sprite->x_incrementer = (sprite->draw_width * 2) / sprite->vars.width;
	x = sprite->screen_x - sprite->draw_width;
	sprite->vars.position_x = 0;
	while (sprite->vars.position_x <= sprite->vars.width)
	{
		y = sprite->screen_y - sprite->draw_height;
		i = -1;
		while (++i < sprite->vars.height)
		{
			coords = coords_init(x, y, x + sprite->x_incrementer, y + sprite->y_incrementer);
			colour = ((unsigned int *)sprite->vars.img.addr)[i * sprite->vars.width + sprite->vars.position_x];
			if (colour != 0x000000)
				draw_square(vars, sprite, coords, colour);
			y += sprite->y_incrementer;
		}
		sprite->vars.position_x++;
		x += sprite->x_incrementer;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:40:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/15 11:58:17 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_wall(t_vars *vars)
{
	int		wall;

	wall = '0';
	vars->wall.east_west_hit = 0;
	while (wall != '1')
	{
		vars->ray.x += vars->ray.cos;
		wall = vars->map.map[(int)vars->ray.y][(int)vars->ray.x];
		if (wall == '1')
		{
			vars->wall.east_west_hit = 1;
			break ;
		}
		vars->ray.y += vars->ray.sin;
		wall = vars->map.map[(int)vars->ray.y][(int)vars->ray.x];
	}
}

void	calc_dist_and_wall_height(t_vars *vars)
{
	float	x_square;
	float	y_square;

	find_wall(vars);
	x_square = pow(vars->player.x - vars->ray.x, 2);
	y_square = pow(vars->player.y - vars->ray.y, 2);
	vars->wall.distance = sqrt(x_square + y_square);
	if (vars->sprite_count > 0)
		vars->wall.dist[vars->ray.count] = vars->wall.distance;
	vars->wall.distance = vars->wall.distance * cos((vars->ray.angle -
				vars->player.angle) * M_PI / 180);
	vars->wall.height = (int)((vars->window.height / 2) / vars->wall.distance);
	if (vars->ray.count == vars->window.width / 2)
		vars->wall.mid_dist = vars->wall.distance;
}

void	paint(int x, t_vars *vars)
{
	t_linecoords	coords;
	t_texvars		texture;

	texture = init_texture(vars);
	coords = coords_init(x, 0, x, vars->window.height / 2 - vars->wall.height);
	dda_line_algorithm(vars, coords, 0xC4E7F7);
	paint_texture(vars, texture, x);
	coords = coords_init(x, vars->window.height / 2 + vars->wall.height,
		x, vars->window.height);
	dda_line_algorithm(vars, coords, 0x009000);
}

void	sprites_info_and_draw(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->sprite_count)
	{
		calculate_sprite_info(vars, &vars->sprite[i]);
		i++;
	}
	if (vars->sprite_count > 1)
		sort_sprite_array(vars);
	i = 0;
	while (i < vars->sprite_count)
	{
		paint_sprite(vars, &vars->sprite[i]);
		i++;
	}
}

int		raycasting(t_vars *vars)
{
	player_move(vars);
	vars->ray.angle = vars->player.angle - vars->player.halffov;
	vars->ray.angle += (vars->ray.angle < 0) ? 360 : 0;
	vars->ray.angle0 = vars->ray.angle;
	vars->ray.increment_angle = vars->player.fov / vars->window.width;
	vars->ray.count = 0;
	vars->ray.precision = 256;
	while (vars->ray.count < vars->window.width)
	{
		vars->ray.x = vars->player.x;
		vars->ray.y = vars->player.y;
		vars->ray.sin = sin(vars->ray.angle * M_PI / 180) / vars->ray.precision;
		vars->ray.cos = cos(vars->ray.angle * M_PI / 180) / vars->ray.precision;
		calc_dist_and_wall_height(vars);
		paint(vars->ray.count, vars);
		vars->ray.angle += vars->ray.increment_angle;
		vars->ray.count++;
	}
	sprites_info_and_draw(vars);
	mlx_put_image_to_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win,
			vars->img.img, 0, 0);
	return (0);
}

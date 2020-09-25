/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:40:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/25 13:16:43 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_vars *vars)
{
	if (vars->keys.left_rotation == 1)
	{
		if ((vars->player.angle - vars->player.rotation) < 0)
			vars->player.angle = 360 + (vars->player.angle - vars->player.rotation);
		else
			vars->player.angle -= vars->player.rotation;
	}	
	if (vars->keys.right_rotation == 1)
	{
		if ((vars->player.angle + vars->player.rotation) > 360)
			vars->player.angle = 360 - (vars->player.angle - vars->player.rotation);
		else
			vars->player.angle += vars->player.rotation;
	}
	if (vars->keys.fw_traslation == 1)
		forward_traslation(vars);
	if (vars->keys.bw_traslation == 1)
		backward_traslation(vars);
	if (vars->keys.left_traslation == 1)
		left_traslation(vars);
	if (vars->keys.right_traslation == 1)
		right_traslation(vars);
}

void	find_wall(t_vars *vars)
{
	int		wall;

	wall = 0;
	vars->wall.east_west_hit = 0;
	while (wall == 0 || wall == 5 || wall == 2)
	{
		vars->ray.x += vars->ray.cos;
		wall = map[(int)vars->ray.y][(int)vars->ray.x];
		if (wall != 0 && wall != 5 && wall != 2)
		{
			vars->wall.east_west_hit = 1;
			break ;
		}
		vars->ray.y += vars->ray.sin;
		wall = map[(int)vars->ray.y][(int)vars->ray.x];
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
	vars->wall.distance = vars->wall.distance * cos((vars->ray.angle -
				vars->player.angle) * M_PI / 180);
	vars->wall.height = (int)((SCREEN_HEIGHT / 2) / vars->wall.distance);
	if (vars->ray.count == SCREEN_WIDTH / 2)
		vars->wall.mid_dist = vars->wall.distance;
}

void	paint(int x, t_vars *vars)
{
	t_linecoords	coords;
	t_texvars		texture;

	texture = init_texture(vars);
	coords = coords_init(x, 0, x, SCREEN_HEIGHT / 2 - vars->wall.height);
	dda_line_algorithm(&vars->img, coords, 0xC4E7F7);
	paint_texture(vars, texture, x);
	coords = coords_init(x, SCREEN_HEIGHT / 2 + vars->wall.height,
		x, SCREEN_HEIGHT);
	dda_line_algorithm(&vars->img, coords, 0x009000);
}

int		raycasting(t_vars *vars)
{
	int	i;
	
	player_move(vars);
	vars->ray.angle = vars->player.angle - vars->player.halffov;
	vars->ray.angle += (vars->ray.angle < 0) ? 360 : 0;
	vars->ray.angle0 = vars->ray.angle;
	vars->ray.increment_angle = vars->player.fov / SCREEN_WIDTH;
	vars->ray.count = 0;
	vars->ray.precision = 256;
	while (vars->ray.count < SCREEN_WIDTH)
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
	i = 0;
	while (i < vars->sprite_count)
	{
		calculate_sprite_info(vars, &vars->sprite[i]);
		i++;
	}
	printf("%d, %f\n", vars->sprite[vars->sprite_count - 1].numero, vars->sprite[vars->sprite_count - 1].screen_x);

	i = 0;
	if (vars->sprite_count > 1)
		sort_sprite_array(vars);
	i = 0;
	while (i < vars->sprite_count)
	{
		paint_sprite(vars, &vars->sprite[i]);
		i++;
	}
	mlx_put_image_to_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win,
			vars->img.img, 0, 0);
	return (0);
}

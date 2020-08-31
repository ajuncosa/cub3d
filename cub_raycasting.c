/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:40:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/08/31 12:00:09 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_vars *vars)
{
	if (vars->keys.left_rotation == 1)
		vars->player.angle -= vars->player.rotation;
	if (vars->keys.right_rotation == 1)
		vars->player.angle += vars->player.rotation;
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
	while (wall == 0 || wall == 5)
	{
		vars->ray.x += vars->ray.cos;
		wall = map[(int)vars->ray.y][(int)vars->ray.x];
		vars->ray.y += vars->ray.sin;
		if (wall != 0 && wall != 5)
		{
			vars->wall.east_west_hit = 1;
			break ;
		}
		wall = map[(int)vars->ray.y][(int)vars->ray.x];
	}
}

void	calculate_wall_height(t_vars *vars)
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
}

void	paint(int x, t_imgdata *img, t_vars *vars)
{
	t_linecoords	coords;

	coords.x0 = x;
	coords.y0 = 0;
	coords.x1 = x;
	coords.y1 = SCREEN_HEIGHT / 2 - vars->wall.height;
	dda_line_algorithm(img, coords, 0xC4E7F7);
	paint_texture(img, vars, x);
	coords.y0 = SCREEN_HEIGHT / 2 + vars->wall.height;
	coords.y1 = SCREEN_HEIGHT;
	dda_line_algorithm(img, coords, 0x00FF00);
}

int		raycasting(t_vars *vars)
{
	t_imgdata	img;

	img.img = mlx_new_image(vars->mlxvars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	player_move(vars);
	vars->ray.angle = vars->player.angle - vars->player.halffov;
	vars->ray.increment_angle = vars->player.fov / SCREEN_WIDTH;
	vars->ray.count = 0;
	vars->ray.precision = 64;
	while (vars->ray.count < SCREEN_WIDTH)
	{
		vars->ray.x = vars->player.x;
		vars->ray.y = vars->player.y;
		vars->ray.sin = sin(vars->ray.angle * M_PI / 180) / vars->ray.precision;
		vars->ray.cos = cos(vars->ray.angle * M_PI / 180) / vars->ray.precision;
		calculate_wall_height(vars);
		texture_position_x_init(vars);
		paint(vars->ray.count, &img, vars);
		vars->ray.angle += vars->ray.increment_angle;
		if (vars->ray.count == SCREEN_WIDTH / 2)
			vars->wall.mid_dist = vars->wall.distance;
		vars->ray.count++;
	}
	mlx_put_image_to_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win,
			img.img, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:16:15 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/07/28 10:19:54 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray_pos_and_path_incrementer(t_vars *vars)
{
	vars->ray.x = vars->player.x;
	vars->ray.y = vars->player.y;
	vars->ray.sin = sin(vars->ray.angle * M_PI / 180) / vars->ray.precision;
	vars->ray.cos = cos(vars->ray.angle * M_PI / 180) / vars->ray.precision;
}

void	find_wall(t_vars *vars)
{
	int		wall;

	wall = 0;
	vars->wall.east_west_hit = 0;
	while (wall == 0)
	{
		vars->ray.x += vars->ray.cos;
		wall = map[(int)vars->ray.y][(int)vars->ray.x];
		vars->ray.y += vars->ray.sin;
		if (wall != 0)
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
	if (vars->wall.height > SCREEN_HEIGHT / 2)
		vars->wall.height = SCREEN_HEIGHT / 2;
}

void	paint(int i, t_imgdata *img, t_vars *vars)
{
	int j;

	j = 0;
	while (j < (SCREEN_HEIGHT / 2 - vars->wall.height))
	{
		my_mlx_pixel_put(img, i, j, 0x00FFFFFF);
		j++;
	}
	while (j >= (SCREEN_HEIGHT / 2 - vars->wall.height) &&
			j < (SCREEN_HEIGHT / 2 + vars->wall.height))
	{
		if (vars->wall.east_west_hit == 0)
		{
			if (vars->ray.sin > 0)
				my_mlx_pixel_put(img, i, j, 0x00FF0000);
			else if (vars->ray.sin < 0)
				my_mlx_pixel_put(img, i, j, 0x00FF00FF);
		}
		else
		{
			if (vars->ray.cos > 0)
				my_mlx_pixel_put(img, i, j, 0x0000000F);
			else if (vars->ray.cos < 0)
				my_mlx_pixel_put(img, i, j, 0x000000FF);
		}
		j++;
	}
	while (j < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(img, i, j, 0x0000FF00);
		j++;
	}
}

int		raycasting(t_vars *vars)
{
	t_imgdata	img;
	int			i;

	img.img = mlx_new_image(vars->mlxvars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	vars->ray.angle = vars->player.angle - vars->player.halffov;
	vars->ray.increment_angle = vars->player.fov / SCREEN_WIDTH;
	vars->ray.count = 0;
	vars->ray.precision = 64;
	i = 0;
	while (vars->ray.count < SCREEN_WIDTH)
	{
		calculate_ray_pos_and_path_incrementer(vars);
		calculate_wall_height(vars);
		paint(i, &img, vars);
		i++;
		vars->ray.angle += vars->ray.increment_angle;
		vars->ray.count++;
	}
	mlx_put_image_to_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win,
			img.img, 0, 0);
	return (0);
}

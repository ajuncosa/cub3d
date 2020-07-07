/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:16:15 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/07/07 13:20:28 by ajuncosa         ###   ########.fr       */
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

float	calculate_wall_height(t_vars *vars)
{
	int		wall;
	float	distance;
	float	wall_height;
	float	x_square;
	float	y_square;

	wall = 0;
	while (wall == 0)
	{
		vars->ray.x += vars->ray.cos;
		vars->ray.y += vars->ray.sin;
		wall = map[(int)vars->ray.y][(int)vars->ray.x];
	}
	x_square = pow(vars->player.x - vars->ray.x, 2);
	y_square = pow(vars->player.y - vars->ray.y, 2);
	distance = sqrt(x_square + y_square);
	distance = distance * cos((vars->ray.angle - vars->player.angle)
			* M_PI / 180);
	wall_height = (int)((SCREEN_HEIGHT / 2) / distance);
	if (wall_height > SCREEN_HEIGHT / 2)
		wall_height = SCREEN_HEIGHT / 2;
	return (wall_height);
}

void	paint(int i, float wall_height, t_imgdata *img)
{
	int j;

	j = 0;
	while (j < (SCREEN_HEIGHT / 2 - wall_height))
	{
		my_mlx_pixel_put(img, i, j, 0x00FFFFFF);
		j++;
	}
	while (j >= (SCREEN_HEIGHT / 2 - wall_height) &&
			j < (SCREEN_HEIGHT / 2 + wall_height))
	{
		my_mlx_pixel_put(img, i, j, 0x00FF0000);
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
	float		wall_height;

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
		wall_height = calculate_wall_height(vars);
		paint(i, wall_height, &img);
		i++;
		vars->ray.angle += vars->ray.increment_angle;
		vars->ray.count++;
	}
	mlx_put_image_to_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win,
			img.img, 0, 0);
	return (0);
}

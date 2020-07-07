/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 10:01:06 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/07/07 12:04:05 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	left_traslation(t_vars *vars)
{
	float	new_x;
	float	new_y;
	float	angle_radians;

	angle_radians = (vars->player.angle - 90) * M_PI / 180;
	vars->player.sin = sin(angle_radians) * vars->player.speed;
	vars->player.cos = cos(angle_radians) * vars->player.speed;
	new_x = vars->player.x + vars->player.cos;
	new_y = vars->player.y + vars->player.sin;
	if (map[(int)new_y][(int)new_x] == 0)
	{
		vars->player.x = new_x;
		vars->player.y = new_y;
	}
}

void	right_traslation(t_vars *vars)
{
	float	new_x;
	float	new_y;
	float	angle_radians;

	angle_radians = (vars->player.angle + 90) * M_PI / 180;
	vars->player.sin = sin(angle_radians) * vars->player.speed;
	vars->player.cos = cos(angle_radians) * vars->player.speed;
	new_x = vars->player.x + vars->player.cos;
	new_y = vars->player.y + vars->player.sin;
	if (map[(int)new_y][(int)new_x] == 0)
	{
		vars->player.x = new_x;
		vars->player.y = new_y;
	}
}

void	forward_traslation(t_vars *vars)
{
	float	new_x;
	float	new_y;
	float	angle_radians;

	angle_radians = vars->player.angle * M_PI / 180;
	vars->player.sin = sin(angle_radians) * vars->player.speed;
	vars->player.cos = cos(angle_radians) * vars->player.speed;
	new_x = vars->player.x + vars->player.cos;
	new_y = vars->player.y + vars->player.sin;
	if (map[(int)new_y][(int)new_x] == 0)
	{
		vars->player.x = new_x;
		vars->player.y = new_y;
	}
}

void	backward_traslation(t_vars *vars)
{
	float	new_x;
	float	new_y;
	float	angle_radians;

	angle_radians = vars->player.angle * M_PI / 180;
	vars->player.sin = sin(angle_radians) * vars->player.speed;
	vars->player.cos = cos(angle_radians) * vars->player.speed;
	new_x = vars->player.x - vars->player.cos;
	new_y = vars->player.y - vars->player.sin;
	if (map[(int)new_y][(int)new_x] == 0)
	{
		vars->player.x = new_x;
		vars->player.y = new_y;
	}
}

int		handle_keys(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win);
		exit(0);
	}
	else if (keycode == 123)
		vars->player.angle -= vars->player.rotation;
	else if (keycode == 124)
		vars->player.angle += vars->player.rotation;
	else if (keycode == 0)
		left_traslation(vars);
	else if (keycode == 2)
		right_traslation(vars);
	else if (keycode == 13)
		forward_traslation(vars);
	else if (keycode == 1)
		backward_traslation(vars);
	return (0);
}

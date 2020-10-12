/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:29:56 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/12 10:18:23 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_vars *vars)
{
	if (vars->keys.left_rotation == 1)
	{
		vars->player.angle -= vars->player.rotation;
		vars->player.angle += vars->player.angle < 0 ? 360 : 0;
	}
	if (vars->keys.right_rotation == 1)
	{
		vars->player.angle += vars->player.rotation;
		vars->player.angle -= vars->player.angle > 360 ? 360 : 0;
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
	if (map[(int)new_y][(int)new_x] == 0 || map[(int)new_y][(int)new_x] == 5)
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
	if (map[(int)new_y][(int)new_x] == 0 || map[(int)new_y][(int)new_x] == 5)
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
	int		one;

	angle_radians = vars->player.angle * M_PI / 180;
	vars->player.sin = sin(angle_radians) * vars->player.speed;
	vars->player.cos = cos(angle_radians) * vars->player.speed;
	new_x = vars->player.x + vars->player.cos;
	new_y = vars->player.y + vars->player.sin;
	if (map[(int)new_y][(int)new_x] == 0 || map[(int)new_y][(int)new_x] == 5)
	{
		if (vars->wall.mid_dist < 0.6)
			return ;
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
	if (map[(int)new_y][(int)new_x] == 0 || map[(int)new_y][(int)new_x] == 5)
	{
		vars->player.x = new_x;
		vars->player.y = new_y;
	}
}

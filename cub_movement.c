/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:29:56 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/23 12:25:59 by ajuncosa         ###   ########.fr       */
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
	/*	if (vars->player.cos > 0)
 			one = 1;
 		else
 			one = -1;
 		if (map[(int)new_y][(int)new_x + one] == 1)
 		{
 			if ((floor(new_x + one) - new_x) < 0.5)
 				return;
 		}
 		if (vars->player.sin > 0)
 			one = 1;
 		else
 			one = -1;
 		if (map[(int)new_y + one][(int)new_x] == 1)
 		{
 			if ((floor(new_y + one) - new_y) < 0.5)
 				return;
 		}*/
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 10:01:06 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/26 17:12:19 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_keys(t_vars *vars)
{
	vars->keys.fw_traslation = 0;
	vars->keys.bw_traslation = 0;
	vars->keys.left_traslation = 0;
	vars->keys.right_traslation = 0;
	vars->keys.left_rotation = 0;
	vars->keys.right_rotation = 0;
}

int		handle_keypress(int keycode, t_vars *vars)
{
	if (keycode == 53)
		exit_programme(vars);
	else if (keycode == 123)
		vars->keys.left_rotation = 1;
	else if (keycode == 124)
		vars->keys.right_rotation = 1;
	else if (keycode == 0)
		vars->keys.left_traslation = 1;
	else if (keycode == 2)
		vars->keys.right_traslation = 1;
	else if (keycode == 13)
		vars->keys.fw_traslation = 1;
	else if (keycode == 1)
		vars->keys.bw_traslation = 1;
	else if (keycode == 15 && vars->hearts.n == 0)
		vars->hearts.n = 3;
	return (0);
}

int		handle_keyrelease(int keycode, t_vars *vars)
{
	if (keycode == 123)
		vars->keys.left_rotation = 0;
	else if (keycode == 124)
		vars->keys.right_rotation = 0;
	else if (keycode == 0)
		vars->keys.left_traslation = 0;
	else if (keycode == 2)
		vars->keys.right_traslation = 0;
	else if (keycode == 13)
		vars->keys.fw_traslation = 0;
	else if (keycode == 1)
		vars->keys.bw_traslation = 0;
	return (0);
}

int		xbutton_close(t_vars *vars)
{
	exit_programme(vars);
	return (0);
}

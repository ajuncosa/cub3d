/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 10:01:06 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/07/28 13:31:35 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		handle_keypress(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win);
		exit(0);
	}
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

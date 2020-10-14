/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/14 13:33:49 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_variables(t_vars *vars)
{
	if (vars->window.height == -1 || vars->window.width == -1
		|| vars->textures.file_north == NULL
		|| vars->textures.file_south == NULL
		|| vars->textures.file_east == NULL || vars->textures.file_west == NULL
		|| vars->textures.file_sprite == NULL || vars->color.floor[0] == -1
		|| vars->color.floor[1] == -1 || vars->color.floor[2] == -1
		|| vars->color.ceiling[0] == -1 || vars->color.ceiling[1] == -1
		|| vars->color.ceiling[2] == -1)
		return (0);
	return (1);
}

void	initialize_vars(t_vars *vars)
{
	vars->window.width = -1;
	vars->window.height = -1;
	vars->textures.file_north = NULL;
	vars->textures.file_south = NULL;
	vars->textures.file_east = NULL;
	vars->textures.file_west = NULL;
	vars->textures.file_sprite = NULL;
	vars->color.floor[0] = -1;
	vars->color.floor[1] = -1;
	vars->color.floor[2] = -1;
	vars->color.ceiling[0] = -1;
	vars->color.ceiling[1] = -1;
	vars->color.ceiling[2] = -1;
	vars->map.height = 0;
	vars->map.width = 0;
	vars->player.x = -1;
	vars->player.y = -1;
	vars->player.angle = -1;
}

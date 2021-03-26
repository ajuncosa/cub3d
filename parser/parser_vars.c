/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/26 17:12:06 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		check_variables(t_vars *vars)
{
	if (vars->window.height == -1 || vars->window.width == -1
		|| vars->textures.file_north == NULL
		|| vars->textures.file_south == NULL
		|| vars->textures.file_east == NULL || vars->textures.file_west == NULL
		|| vars->textures.file_sprite1 == NULL || vars->color.f[0] == -1
		|| vars->color.f[1] == -1 || vars->color.f[2] == -1
		|| vars->color.c[0] == -1 || vars->color.c[1] == -1
		|| vars->color.c[2] == -1)
	{
		write(1, "Error\nMissing information. Map must be last\n", 44);
		return (0);
	}
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
	vars->textures.file_sprite1 = NULL;
	vars->textures.file_sprite2 = NULL;
	vars->textures.file_sprite3 = NULL;
	vars->color.f[0] = -1;
	vars->color.f[1] = -1;
	vars->color.f[2] = -1;
	vars->color.c[0] = -1;
	vars->color.c[1] = -1;
	vars->color.c[2] = -1;
	vars->map.height = 0;
	vars->map.width = 0;
	vars->player.x = -1;
	vars->player.y = -1;
	vars->player.angle = -1;
	vars->map.map = NULL;
	vars->sprite = NULL;
	vars->wall.dist = NULL;
}

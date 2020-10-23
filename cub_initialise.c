/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_initialise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:21:34 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/23 12:49:17 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_initialise(t_vars *vars)
{
	vars->player.x += 0.5;
	vars->player.y += 0.5;
	vars->player.fov = 60;
	vars->player.halffov = vars->player.fov / 2;
	vars->player.speed = 0.2;
	vars->player.rotation = 3;
}

void	count_sprites(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	j = 0;
	vars->sprite_count = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (vars->map.map[i][j] != '0' && vars->map.map[i][j] != '1'
				&& vars->map.map[i][j] != '9' && vars->map.map[i][j] != ' ')
				vars->sprite_count++;
			j++;
		}
		i++;
	}
}

void	fill_array(t_vars *vars, int i, int j, int *count)
{
	if (vars->map.map[i][j] != '0' && vars->map.map[i][j] != '1'
		&& vars->map.map[i][j] != '9' && vars->map.map[i][j] != ' ')
	{
		vars->sprite[*count].map_x = j + 0.5;
		vars->sprite[*count].map_y = i + 0.5;
		//vars->sprite[*count].id = map[i][j];
		*count += 1;
	}
}

int		init_sprite_array(t_vars *vars)
{
	int i;
	int j;
	int	count;

	count_sprites(vars);
	if (vars->sprite_count == 0)
		return (1);
	if (!(vars->sprite = malloc(vars->sprite_count * sizeof(t_sprite))))
		return (0);
	i = 0;
	count = 0;
	while (i < vars->map.height)
	{
		j = -1;
		while (++j < vars->map.width)
			fill_array(vars, i, j, &count);
		i++;
	}
	if (!(vars->wall.dist = malloc(vars->window.width * sizeof(float))))
		return (0);
	return (1);
}

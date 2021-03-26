/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:38 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/26 17:12:08 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		empty_end_of_line(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	flood_fill(t_vars *vars, int x, int y, int prev_color)
{
	if (x < 0 || x >= vars->map.width || y < 0 || y >= vars->map.height)
		return ;
	if (vars->map.map[y][x] != prev_color
		&& !ft_strchr("234", vars->map.map[y][x]))
		return ;
	if (vars->map.map[y][x] == '2')
		vars->map.map[y][x] = '8';
	else if (vars->map.map[y][x] == '3')
		vars->map.map[y][x] = '7';
	else if (vars->map.map[y][x] == '4')
		vars->map.map[y][x] = '6';
	else
		vars->map.map[y][x] = '9';
	flood_fill(vars, x + 1, y, prev_color);
	flood_fill(vars, x - 1, y, prev_color);
	flood_fill(vars, x, y + 1, prev_color);
	flood_fill(vars, x, y - 1, prev_color);
}

void	sprites_back_to_original_nbr(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (vars->map.map[i][j] == '8')
				vars->map.map[i][j] = '2';
			else if (vars->map.map[i][j] == '7')
				vars->map.map[i][j] = '3';
			else if (vars->map.map[i][j] == '6')
				vars->map.map[i][j] = '4';
			j++;
		}
		i++;
	}
}

int		check_player_pos(t_vars *vars, int y, char *str)
{
	int x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == 'N')
			vars->player.angle = 270;
		else if (str[x] == 'S')
			vars->player.angle = 90;
		else if (str[x] == 'E')
			vars->player.angle = 0;
		else if (str[x] == 'W')
			vars->player.angle = 180;
		if (ft_strchr("NESW", str[x]))
		{
			if (vars->player.x != -1 || vars->player.y != -1)
				return (0);
			vars->player.x = x;
			vars->player.y = y;
			vars->map.map[y][x] = '0';
		}
		x++;
	}
	return (1);
}

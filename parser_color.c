/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/14 12:45:39 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		valid_colors(t_vars *vars, int type)
{
	if (type == 1 && vars->color.ceiling[0] >= 0
		&& vars->color.ceiling[0] <= 255
		&& vars->color.ceiling[1] >= 0 && vars->color.ceiling[1] <= 255
		&& vars->color.ceiling[2] >= 0 && vars->color.ceiling[2] <= 255)
		return (1);
	if (type == 2 && vars->color.floor[0] >= 0 && vars->color.floor[0] <= 255
		&& vars->color.floor[1] >= 0 && vars->color.floor[1] <= 255
		&& vars->color.floor[2] >= 0 && vars->color.floor[2] <= 255)
		return (1);
	return (0);
}

int		save_color(t_vars *vars, int type, int color, char *str)
{
	if (!ft_isdigit(str[0]))
		return (0);
	if (type == 1)
	{
		if (vars->color.ceiling[0] != -1 && vars->color.ceiling[1] != -1 && vars->color.ceiling[2] != -1)
			return (0);
		if (color == 0)
			vars->color.ceiling[0] = ft_atoi(str);
		else if (color == 1)
			vars->color.ceiling[1] = ft_atoi(str);
		else
			vars->color.ceiling[2] = ft_atoi(str);
	}
	else
	{
		if (vars->color.floor[0] != -1 && vars->color.floor[1] != -1 && vars->color.floor[2] != -1)
			return (0);
		if (color == 0)
			vars->color.floor[0] = ft_atoi(str);
		else if (color == 1)
			vars->color.floor[1] = ft_atoi(str);
		else
			vars->color.floor[2] = ft_atoi(str);
	}
	return (1);
}

int		parse_color_line(t_vars *vars, int type, char *str)
{
	int i;
	int	j;

	i = 1;
	if (!ft_isspace(str[i]))
		return (0);
	while (ft_isspace(str[i]))
		i++;
	j = 0;
	while (j < 3)
	{
		if (!save_color(vars, type, j, &str[i]))
			return (0);
		while (ft_isdigit(str[i]))
			i++;
		if (j != 2 && str[i] != ',')
			return (0);
		if (str[i] == ',')
			i++;
		j++;
	}
	if (!empty_end_of_line(&str[i]))
		return (0);
	return (valid_colors(vars, type) == 0 ? 0 : 1);
}

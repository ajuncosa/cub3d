/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/16 12:53:23 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		valid_colors(t_vars *vars, int type)
{
	if (type == 1 && vars->color.c[0] >= 0
		&& vars->color.c[0] <= 255
		&& vars->color.c[1] >= 0 && vars->color.c[1] <= 255
		&& vars->color.c[2] >= 0 && vars->color.c[2] <= 255)
		return (1);
	if (type == 2 && vars->color.f[0] >= 0 && vars->color.f[0] <= 255
		&& vars->color.f[1] >= 0 && vars->color.f[1] <= 255
		&& vars->color.f[2] >= 0 && vars->color.f[2] <= 255)
		return (1);
	return (0);
}

int		save_color(t_color *colors, int type, int color, char *str)
{
	if (!ft_isdigit(str[0]))
		return (0);
	if (type == 1)
	{
		if (colors->c[0] != -1 && colors->c[1] != -1 && colors->c[2] != -1)
			return (0);
		if (color == 0)
			colors->c[0] = ft_atoi(str);
		else if (color == 1)
			colors->c[1] = ft_atoi(str);
		else
			colors->c[2] = ft_atoi(str);
	}
	else
	{
		if (colors->f[0] != -1 && colors->f[1] != -1 && colors->f[2] != -1)
			return (0);
		if (color == 0)
			colors->f[0] = ft_atoi(str);
		else if (color == 1)
			colors->f[1] = ft_atoi(str);
		else
			colors->f[2] = ft_atoi(str);
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
		if (!save_color(&vars->color, type, j, &str[i]))
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

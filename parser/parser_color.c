/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/04 13:06:01 by ajuncosa         ###   ########.fr       */
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
	write(1, "Error\nRGB colours must be in range 0-225\n", 41);
	return (0);
}

int		save_ceiling_color(t_color *colors, int color, char *str)
{
	if (!ft_isdigit(str[0]))
	{
		write(1, "Error\nWrong format in C colour line\n", 36);
		return (0);
	}
	if (colors->c[0] != -1 && colors->c[1] != -1 && colors->c[2] != -1)
	{
		write(1, "Error\nDuplicated C line\n", 24);
		return (0);
	}
	if (color == 0)
		colors->c[0] = ft_atoi(str);
	else if (color == 1)
		colors->c[1] = ft_atoi(str);
	else
		colors->c[2] = ft_atoi(str);
	return (1);
}

int		save_floor_color(t_color *colors, int color, char *str)
{
	if (!ft_isdigit(str[0]))
	{
		write(1, "Error\nWrong format in F colour line\n", 36);
		return (0);
	}
	if (colors->f[0] != -1 && colors->f[1] != -1 && colors->f[2] != -1)
	{
		write(1, "Error\nDuplicated F line\n", 24);
		return (0);
	}
	if (color == 0)
		colors->f[0] = ft_atoi(str);
	else if (color == 1)
		colors->f[1] = ft_atoi(str);
	else
		colors->f[2] = ft_atoi(str);
	return (1);
}

int		hola(t_vars *vars, int type, char *str, int *i)
{
	while (vars->color.r_g_or_b < 3)
	{
		if (type == 1)
		{
			if (!save_ceiling_color(&vars->color,
				vars->color.r_g_or_b, &str[*i]))
				return (0);
		}
		else
		{
			if (!save_floor_color(&vars->color, vars->color.r_g_or_b, &str[*i]))
				return (0);
		}
		while (ft_isdigit(str[*i]))
			*i += 1;
		if (vars->color.r_g_or_b != 2 && str[*i] != ',')
		{
			write(1, "Error\nWrong format in colour line\n", 34);
			return (0);
		}
		if (str[*i] == ',')
			*i += 1;
		vars->color.r_g_or_b++;
	}
	return (1);
}

int		parse_color_line(t_vars *vars, int type, char *str)
{
	int i;

	i = 1;
	vars->color.r_g_or_b = 0;
	if (!ft_isspace(str[i]))
	{
		write(1, "Error\nMissing space after colour type identifier\n", 49);
		return (0);
	}
	while (ft_isspace(str[i]))
		i++;
	if (!hola(vars, type, str, &i))
		return (0);
	if (!empty_end_of_line(&str[i]))
	{
		write(1, "Error\nWrong format in colour line\n", 34);
		return (0);
	}
	return (valid_colors(vars, type));
}

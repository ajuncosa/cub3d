/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:28 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/23 14:09:08 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		save_width_and_height(t_vars *vars, char *str, int *i, int type)
{
	while (ft_isspace(str[*i]))
		*i += 1;
	if (!ft_isdigit(str[*i]))
	{
		write(1, "Error\nWrong format in R line\n", 29);
		return (0);
	}
	if (type == 1)
		vars->window.width = ft_atoi(&str[*i]);
	else
		vars->window.height = ft_atoi(&str[*i]);
	while (ft_isdigit(str[*i]))
		*i += 1;
	return (1);
}

int		parse_resolution_line(t_vars *vars, char *str)
{
	int i;

	i = 1;
	if (vars->window.width != -1 || vars->window.height != -1)
	{
		write(1, "Error\nDuplicated R line\n", 24);
		return (0);
	}
	if (!ft_isspace(str[i]))
	{
		write(1, "Error\nMissing space after R type identifier\n", 42);
		return (0);
	}
	if (!save_width_and_height(vars, str, &i, 1))
		return (0);
	if (!save_width_and_height(vars, str, &i, 2))
		return (0);
	if (!empty_end_of_line(&str[i]))
	{
		write(1, "Error\nWrong format in R line\n", 29);
		return (0);
	}
	return (1);
}

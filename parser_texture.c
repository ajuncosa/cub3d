/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:34 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/11 12:15:24 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_null_texture(t_vars *vars, int type)
{
	if (type == 1)
		return (vars->textures.file_north != NULL ? 0 : 1);
	else if (type == 2)
		return (vars->textures.file_south != NULL ? 0 : 1);
	else if (type == 3)
		return (vars->textures.file_east != NULL ? 0 : 1);
	else if (type == 4)
		return (vars->textures.file_west != NULL ? 0 : 1);
	else if (type == 5)
		return (vars->textures.file_sprite1 != NULL ? 0 : 1);
	else if (type == 6)
		return (vars->textures.file_sprite2 != NULL ? 0 : 1);
	else
		return (vars->textures.file_sprite3 != NULL ? 0 : 1);
}

int		save_texture_dir(t_vars *vars, int type, char *str)
{
	if (!is_null_texture(vars, type))
	{
		write(1, "Error\nDuplicated texture lines\n", 31);
		return (0);
	}
	if (type == 1)
		vars->textures.file_north = ft_strtrim(str, " \t\n\v\f\r");
	else if (type == 2)
		vars->textures.file_south = ft_strtrim(str, " ");
	else if (type == 3)
		vars->textures.file_east = ft_strtrim(str, " ");
	else if (type == 4)
		vars->textures.file_west = ft_strtrim(str, " ");
	else if (type == 5)
		vars->textures.file_sprite1 = ft_strtrim(str, " ");
	else if (type == 6)
		vars->textures.file_sprite2 = ft_strtrim(str, " ");
	else
		vars->textures.file_sprite3 = ft_strtrim(str, " ");
	return (1);
}

int		parse_texture_line(t_vars *vars, int type, char *str)
{
	int i;

	i = (type == 5) ? 1 : 2;
	if (!ft_isspace(str[i]))
	{
		write(1, "Error\nMissing space after texture type identifier\n", 50);
		return (0);
	}
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isascii(str[i]))
	{
		write(1, "Error\nWrong texture string\n", 27);
		return (0);
	}
	if (!save_texture_dir(vars, type, &str[i]))
		return (0);
	return (1);
}

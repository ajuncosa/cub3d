/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:34 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/05 11:40:10 by ajuncosa         ###   ########.fr       */
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
	else
		return (vars->textures.file_sprite != NULL ? 0 : 1);
}

int		save_texture_dir(t_vars *vars, int type, char *str)
{
	char	*check;

	if (!is_null_texture(vars, type))
	{
		write(1, "Error\nDuplicated texture lines\n", 31);
		return (0);
	}
	if (type == 1)
		vars->textures.file_north = ft_strdup(str);
	else if (type == 2)
		vars->textures.file_south = ft_strdup(str);
	else if (type == 3)
		vars->textures.file_east = ft_strdup(str);
	else if (type == 4)
		vars->textures.file_west = ft_strdup(str);
	else
		vars->textures.file_sprite = ft_strdup(str);
	check = ft_strrchr(str, '.');
	if (check == 0 || ft_strncmp(check, ".xpm", 5))
	{
		write(1, "Error\nTexture file must be .xpm\n", 32);
		return (0);
	}
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

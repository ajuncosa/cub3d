/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:14:32 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/05 11:36:30 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	args_and_file_error_management(t_vars *vars, int argc, char **argv)
{
	char	*check;

	if (argc < 2 || argc > 3)
	{
		write(1, "Error\nWrong no of arguments\n", 28);
		return (0);
	}
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
	{
		write(1,
			"Error\nProgramme only takes \"--save\" as second argument\n", 55);
		return (0);
	}
	check = ft_strrchr(argv[1], '.');
	if (check == 0 || ft_strncmp(check, ".cub", 5))
	{
		write(1, "Error\nInvalid name of file\n", 27);
		return (0);
	}
	if (!read_file(vars, argv[1]))
		return (0);
	return (1);
}

int	init_player_keys_tex_sprite(t_vars *vars)
{
	player_initialise(vars);
	init_keys(vars);
	if (!init_sprite_array(vars))
	{
		write(1, "Error\nCould not init sprite array\n", 34);
		mlx_destroy_image(vars->mlxvars.mlx, vars->img.img);
		return (0);
	}
	if (!init_all_textures(vars))
	{
		write(1, "Error\nInvalid texture file\n", 27);
		mlx_destroy_image(vars->mlxvars.mlx, vars->img.img);
		free(vars->sprite);
		free(vars->wall.dist);
		return (0);
	}
	return (1);
}

int	bmp_check(t_vars *vars)
{
	vars->save_arg = 1;
	if (!create_bmp(vars))
	{
		write(1, "Error\nCould not render bmp file\n", 32);
		return (0);
	}
	return (1);
}

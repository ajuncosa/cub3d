/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:14:32 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/11 12:12:37 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_programme(t_vars *vars)
{
	int	i;

	i = 0;
	mlx_destroy_image(vars->mlxvars.mlx, vars->img.img);
	free(vars->sprite);
	free(vars->wall.dist);
	free(vars->textures.file_east);
	free(vars->textures.file_west);
	free(vars->textures.file_north);
	free(vars->textures.file_south);
	free(vars->textures.file_sprite1);
	free(vars->textures.file_sprite2);
	free(vars->textures.file_sprite3);
	if (vars->map.map)
	{
		while (i < vars->map.height)
		{
			free(vars->map.map[i]);
			i++;
		}
		free(vars->map.map);
	}
	if (vars->mlxvars.mlx_win)
		mlx_destroy_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win);
	exit(0);
}

void	error_parsing_exit(t_vars *vars, int fd)
{
	int	i;

	i = 0;
	free(vars->textures.file_east);
	free(vars->textures.file_west);
	free(vars->textures.file_north);
	free(vars->textures.file_south);
	free(vars->textures.file_sprite1);
	free(vars->textures.file_sprite2);
	free(vars->textures.file_sprite3);
	if (vars->map.map)
	{
		while (i < vars->map.height)
		{
			free(vars->map.map[i]);
			i++;
		}
		free(vars->map.map);
	}
	close(fd);
	exit(0);
}

void	args_error_management(t_vars *vars, int argc, char **argv)
{
	char	*check;

	if (argc < 2 || argc > 3)
	{
		write(1, "Error\nWrong no of arguments\n", 28);
		exit(0);
	}
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
	{
		write(1,
			"Error\nProgramme only takes \"--save\" as second argument\n", 55);
		exit(0);
	}
	check = ft_strrchr(argv[1], '.');
	if (check == 0 || ft_strncmp(check, ".cub", 5))
	{
		write(1, "Error\nInvalid name of file\n", 27);
		exit(0);
	}
}

void	init_player_keys_tex_sprite(t_vars *vars)
{
	int	i;

	i = 0;
	player_initialise(vars);
	init_keys(vars);
	if (!init_sprite_array(vars))
	{
		write(1, "Error\nCould not init sprite array\n", 34);
		exit_programme(vars);
	}
	if (!init_all_textures(vars))
	{
		write(1, "Error\nInvalid texture file\n", 27);
		exit_programme(vars);
	}
}

void	bmp_check(t_vars *vars)
{
	vars->save_arg = 1;
	if (!create_bmp(vars))
	{
		write(1, "Error\nCould not render bmp file\n", 32);
		exit_programme(vars);
	}
	exit_programme(vars);
}

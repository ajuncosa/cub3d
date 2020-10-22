/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:42:59 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/21 14:04:47 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_vars		vars;
	int			file_ok;
	int			i;

	if (argc != 2)
	{
		write(1, "Error: wrong no of arguments\n", 30);
		return (1);
	}
	i = 0;
	while (argv[1][i] != '.' && argv[1][i] != '\0')
		i++;
	if (ft_strncmp(&argv[1][i], ".cub", 5))
	{
		write(1, "Error: invalid name of file\n", 29);
		return (1);
	}
	file_ok = read_file(&vars, argv[1]);
	if (!file_ok)
	{
		write(1, "Error: something wrong in the file\n", 36);
		return (1);
	}
	player_initialise(&vars);
	init_keys(&vars);
	if (!init_sprite_array(&vars))
	{
		printf("error\n");
		return (1);
	}
	vars.mlxvars.mlx = mlx_init();
	vars.mlxvars.mlx_win = mlx_new_window(vars.mlxvars.mlx,
			vars.window.width, vars.window.height, "Hello world!");
	if (!init_all_textures(&vars))
	{
		printf("error\n");
		return (1);
	}

	vars.img.img = mlx_new_image(vars.mlxvars.mlx, vars.window.width, vars.window.height);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
			&vars.img.line_length, &vars.img.endian);
	mlx_loop_hook(vars.mlxvars.mlx, raycasting, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 2, 0L, handle_keypress, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 3, 0L, handle_keyrelease, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 17, 0L, xbutton_close, &vars);
	mlx_loop(vars.mlxvars.mlx);
	mlx_destroy_image(vars.mlxvars.mlx, vars.img.img);
	free(vars.sprite);
	free(vars.wall.dist);
	return (0);
}

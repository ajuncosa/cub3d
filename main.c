/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:42:59 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/30 13:19:57 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_vars		vars;
	int			file_ok;
	int			i;

// MEJORAR ERRORES DE LOS ARGUMENTOS o si el 2º arg no es --save
	if (argc < 2 || argc > 3)
	{
		write(1, "Error\nWrong no of arguments\n", 28);
		return (1);
	}


	i = 0;
	// COMPROBAR QUE TEXTURAS SON XPM
	// USAR STRRCRH PARA BUSCAR EL PUNTO DESDE ATRÁS EN VEZ DE ESTO POR SI HAY MAS DE UN PUNTO
	while (argv[1][i] != '.' && argv[1][i] != '\0')
		i++;
	if (ft_strncmp(&argv[1][i], ".cub", 5))
	{
		write(1, "Error\nInvalid name of file\n", 27);
		return (1);
	}

	file_ok = read_file(&vars, argv[1]);
	if (!file_ok)
		return (1);
	player_initialise(&vars);
	init_keys(&vars);
	if (!init_sprite_array(&vars))
	{
		write(1, "Error\nCould not init sprite array\n", 34);
		return (1);
	}
	vars.mlxvars.mlx = mlx_init();
	vars.mlxvars.mlx_win = mlx_new_window(vars.mlxvars.mlx,
			vars.window.width, vars.window.height, "Hello world!");
	if (!init_all_textures(&vars))
	{
		write(1, "Error\nInvalid texture file\n", 27);
		return (1);
	}
	
	vars.img.img = mlx_new_image(vars.mlxvars.mlx, vars.window.width, vars.window.height);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
			&vars.img.line_length, &vars.img.endian);
	vars.save_arg = 0;
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
	{
		vars.save_arg = 1;
		if (!create_bmp(&vars))
		{
			write(1, "Error\nCould not render bmp file\n", 36);
			return (1);
		}
		return (0);
	}
	mlx_loop_hook(vars.mlxvars.mlx, raycasting, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 2, 0L, handle_keypress, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 3, 0L, handle_keyrelease, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 17, 0L, xbutton_close, &vars);
	mlx_loop(vars.mlxvars.mlx);
	// A PARTIR DE AQUÍ NUNCA PASA
	mlx_destroy_image(vars.mlxvars.mlx, vars.img.img);
	free(vars.sprite);
	free(vars.wall.dist);
	return (0);
}

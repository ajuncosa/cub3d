/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:42:59 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/09 10:28:42 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_vars		vars;

	args_error_management(&vars, argc, argv);
	read_file(&vars, argv[1]);
	vars.mlxvars.mlx = mlx_init();
	vars.img.img = mlx_new_image(vars.mlxvars.mlx,
		vars.window.width, vars.window.height);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
		&vars.img.line_length, &vars.img.endian);
	init_player_keys_tex_sprite(&vars);
	vars.save_arg = 0;
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
		bmp_check(&vars);
	vars.mlxvars.mlx_win = mlx_new_window(vars.mlxvars.mlx,
		vars.window.width, vars.window.height, "Hello world!");
	mlx_loop_hook(vars.mlxvars.mlx, raycasting, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 2, 0L, handle_keypress, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 3, 0L, handle_keyrelease, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 17, 0L, xbutton_close, &vars);
	mlx_loop(vars.mlxvars.mlx);
	return (0);
}

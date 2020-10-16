/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:42:59 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/16 11:41:11 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	player_initialise(t_vars *vars)
{

	vars->player.x += 0.5;
	vars->player.y += 0.5;
	vars->player.fov = 60;
	vars->player.halffov = vars->player.fov / 2;
	vars->player.speed = 0.2;
	vars->player.rotation = 3;
}

int		main(int argc, char **argv)
{
	t_vars		vars;
	int			file_ok;

	if (argc != 2)
	{
		write(1, "Error: wrong no of arguments\n", 30);
		return (1);
	}
	file_ok = read_file(&vars, argv[1]);
	if (!file_ok)
	{
		write(1, "Error: something wrong in the file\n", 36);
		return (1);
	}

	/*printf("file: %d\n", file_ok);
	printf("===FILE %s===\n", (file_ok == 1) ? "OK" : "BAD");
	printf("\n====VARS====\n");
	printf("window: %d x %d\n", vars.window.width, vars.window.height);
	printf("texture_north: %s \n", vars.textures.file_north);
	printf("texture_east: %s \n", vars.textures.file_east);
	printf("texture_west: %s \n", vars.textures.file_west);
	printf("texture_south: %s \n", vars.textures.file_south);
	printf("sprite_texture: %s \n", vars.textures.file_sprite);
	printf("Floor color: %d,%d,%d\n", vars.color.floor[0], vars.color.floor[1], vars.color.floor[2]);
	printf("Ceiling color: %d,%d,%d\n", vars.color.ceiling[0], vars.color.ceiling[1], vars.color.ceiling[2]);
	printf("map_width: %d \n", vars.map.width);
	printf("map_height: %d \n", vars.map.height);
	printf("player_x: %f \n", vars.player.x);
	printf("player_y: %f \n", vars.player.y);
	printf("player_dir: %f \n", vars.player.angle);
	int y = 0, x;
	while (y < vars.map.height)
	{
		x = 0;
		while (x < vars.map.width)
		{
			printf("%c", vars.map.map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}*/

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

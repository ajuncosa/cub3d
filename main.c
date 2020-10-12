/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:42:59 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/12 10:31:43 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,2,0,0,0,0,1},
        {1,0,2,0,0,0,0,0,0,1},
        {1,0,0,0,5,0,0,0,2,1},
        {1,0,0,0,0,0,0,0,2,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,0,2,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };

/*
void	map_initialise(t_vars *vars)
{
	
}
*/

void	player_initialise(t_vars *vars)
{
	int i;
	int j;

	j = 0;
	while (j < MAP_HEIGHT)
	{
		i = 0;
		while (i < MAP_WIDTH)
		{
			if (map[j][i] == 5)
			{
				vars->player.x = i + 0.5;
				vars->player.y = j + 0.5;
				break;
			}
			i++;
		}
		j++;
	}
	vars->player.angle = 270;
	vars->player.fov = 60;
	vars->player.halffov = vars->player.fov / 2;
	vars->player.speed = 0.2;
	vars->player.rotation = 3;
}

int		main(int argc, char **argv)
{
	t_vars		vars;

//	map_initialise(&vars);

	player_initialise(&vars);
	init_keys(&vars);
	if (!init_sprite_array(&vars))
		return (1);
	vars.mlxvars.mlx = mlx_init();
	vars.mlxvars.mlx_win = mlx_new_window(vars.mlxvars.mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	init_all_textures(&vars);
	vars.img.img = mlx_new_image(vars.mlxvars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
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

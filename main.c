/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:42:59 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/08/27 12:06:34 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1,1},
        {1,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,5,1,0,0,0,1},
        {1,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
/*
void	map_initialise(t_vars *vars)
{
	
}
*/
void	my_mlx_pixel_put(t_imgdata *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		xbutton_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win);
	exit(0);
}

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
				vars->player.x = i;
				vars->player.y = j;
				break;
			}
			i++;
		}
		j++;
	}
	vars->player.angle = 270;
	vars->player.fov = 60;
	vars->player.halffov = vars->player.fov / 2;
	vars->player.speed = 0.0001;
	vars->player.rotation = 3;
}

int		main(int argc, char **argv)
{
	t_vars		vars;
/*	int		fd;
	size_t	bytes;
	char	*map;

	if (!(map = malloc((WIDTH * HEIGHT) + 1)))
		return(-1);
	fd = open(argv[1], O_RDONLY);
	bytes = read(fd, map, WIDTH * HEIGHT);
	map[bytes] = '\0';
	if (close(fd) < 0)
	{
		printf("k patsa\n");
		return(-1);
	}
	printf("%s\n", map);
*/
//	map_initialise(&vars);
	player_initialise(&vars);
	vars.mlxvars.mlx = mlx_init();
	vars.mlxvars.mlx_win = mlx_new_window(vars.mlxvars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	east_west_textures_init(&vars);
	north_south_textures_init(&vars);
	mlx_loop_hook(vars.mlxvars.mlx, raycasting, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 2, 0L, handle_keypress, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 3, 0L, handle_keyrelease, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 17, 0L, xbutton_close, &vars);
	mlx_loop(vars.mlxvars.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:42:59 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/07/06 09:37:57 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#define	MAP_WIDTH		10
#define	MAP_HEIGHT		10
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_vars
{
	void		*mlx;
	void		*mlx_win;
}				t_vars;

typedef struct	s_player
{
	int			x;
	int			y;
	float		angle;
	float		fov;
	float		halffov;
}				t_player;
/*
typedef struct	s_ray
{
	int			ray_angle;
}
*/
int		map[MAP_HEIGHT][MAP_WIDTH] =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,1,0,0,0,0,1,1},
		{1,0,1,0,0,0,0,0,0,1},
		{1,1,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,1},
		{1,0,0,1,1,1,1,0,0,1},
		{1,0,0,0,0,1,0,5,0,1},
		{1,0,0,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		handle_keys(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(0);
	}
	return(0);
}

int		xbutton_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

void	player_initialise(t_player *player)
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
				player->x = i;
				player->y = j;
				break;
			}
			i++;
		}
		j++;
	}
	player->angle = 270;
	player->fov = 60;
	player->halffov = player->fov / 2;
}

void	raycasting(t_player *player, t_vars *vars)
{
	float	ray_angle;
	float	ray_increment_angle;
	int		ray_count;
	float	ray_x;
	float	ray_y;
	float	ray_precision;
	float	ray_sin;
	float	ray_cos;
	int		wall;
	float	distance;
	float	screen_halfheight;
	float	wall_height;

	t_data	img;
	img.img = mlx_new_image(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	screen_halfheight = SCREEN_HEIGHT / 2;
	ray_angle = player->angle - player->halffov;
	ray_increment_angle = player->fov / SCREEN_WIDTH;
	ray_count = 0;
	ray_precision = 64;

	int i = 0;
	while (ray_count < SCREEN_WIDTH)
	{
		//ray data
		ray_x = player->x;
		ray_y = player->y;
		//ray path incrementers
		ray_sin = sin(ray_angle * M_PI / 180) / ray_precision;
		ray_cos = cos(ray_angle * M_PI / 180) / ray_precision;
		//wall finder
		wall = 0;
		while (wall == 0)
		{
			ray_x += ray_cos;
			ray_y += ray_sin;
			wall = map[(int)ray_y][(int)ray_x];
		}
		//Pythagoras theorem
		distance = sqrt(pow(player->x - ray_x, 2) + pow(player->y - ray_y, 2));
		//wall height
		wall_height = (int)(screen_halfheight / distance);
		if (wall_height > SCREEN_HEIGHT / 2)
			wall_height = SCREEN_HEIGHT / 2;
		//draw
		int j = 0;
		while (j < (screen_halfheight - wall_height))
		{
			my_mlx_pixel_put(&img, i, j, 0x00FFFFFF);
			j++;
		}
		while (j >= (screen_halfheight - wall_height) && j < (screen_halfheight + wall_height))
		{
			my_mlx_pixel_put(&img, i, j, 0x00FF0000);
			j++;
		}
		while (j < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(&img, i, j, 0x0000FF00);
			j++;
		}
		i++;

		ray_angle += ray_increment_angle;
		ray_count++;
	}
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, img.img, 0, 0);
}

int		main(int argc, char **argv)
{
	t_vars		vars;
	t_player	player;

//	int	fd;
//	size_t	bytes;
//	char	*map;

/*	if (!(map = malloc((WIDTH * HEIGHT) + 1)))
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
	player_initialise(&player);
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	raycasting(&player, &vars);
	mlx_hook(vars.mlx_win, 2, 0L, handle_keys, &vars);
	mlx_hook(vars.mlx_win, 17, 0L, xbutton_close, &vars);
	mlx_loop(vars.mlx);
}

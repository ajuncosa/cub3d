/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:42:59 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/07/06 12:18:35 by ajuncosa         ###   ########.fr       */
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

typedef struct	s_imgdata
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_imgdata;

typedef struct	s_mlxvars
{
	void		*mlx;
	void		*mlx_win;
}				t_mlxvars;

typedef struct	s_player
{
	int			x;
	int			y;
	float		angle;
	float		fov;
	float		halffov;
}				t_player;

typedef struct	s_ray
{
	float		angle;
	float		increment_angle;
	int			count;
	float		x;
	float		y;
	float		precision;
	float		sin;
	float		cos;
}				t_ray;

typedef struct	s_vars
{
	t_mlxvars	mlxvars;
	t_player	player;
	t_ray		ray;
}				t_vars;


int		map[MAP_HEIGHT][MAP_WIDTH] =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,1,1},
		{1,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,1},
		{1,0,5,0,1,1,1,0,0,1},
		{1,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

void	my_mlx_pixel_put(t_imgdata *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		handle_keys(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win);
		exit(0);
	}
	if (keycode == 123)
	{
		vars->player.angle -= 5;
	}
	if (keycode == 124)
	{
		vars->player.angle += 5;
	}
	return(0);
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
}

int		raycasting(t_vars *vars)
{
	int		wall;
	float	distance;
	float	screen_halfheight;
	float	wall_height;
	int		i;
	int		j;

	t_imgdata	img;
	img.img = mlx_new_image(vars->mlxvars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	screen_halfheight = SCREEN_HEIGHT / 2;
	vars->ray.angle = vars->player.angle - vars->player.halffov;
	vars->ray.increment_angle = vars->player.fov / SCREEN_WIDTH;
	vars->ray.count = 0;
	vars->ray.precision = 64;

	i = 0;
	while (vars->ray.count < SCREEN_WIDTH)
	{
		//ray data
		vars->ray.x = vars->player.x;
		vars->ray.y = vars->player.y;
		//ray path incrementers
		vars->ray.sin = sin(vars->ray.angle * M_PI / 180) / vars->ray.precision;
		vars->ray.cos = cos(vars->ray.angle * M_PI / 180) / vars->ray.precision;
		//wall finder
		wall = 0;
		while (wall == 0)
		{
			vars->ray.x += vars->ray.cos;
			vars->ray.y += vars->ray.sin;
			wall = map[(int)vars->ray.y][(int)vars->ray.x];
		}
		//Pythagoras theorem & fisheye fix
		distance = sqrt(pow(vars->player.x - vars->ray.x, 2) + pow(vars->player.y - vars->ray.y, 2));
		distance = distance * cos((vars->ray.angle - vars->player.angle) * M_PI / 180);
		//wall height
		wall_height = (int)(screen_halfheight / distance);
		if (wall_height > SCREEN_HEIGHT / 2)
			wall_height = SCREEN_HEIGHT / 2;
		//draw
		j = 0;
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
		vars->ray.angle += vars->ray.increment_angle;
		vars->ray.count++;
	}
	mlx_put_image_to_window(vars->mlxvars.mlx, vars->mlxvars.mlx_win, img.img, 0, 0);
	return(0);
}

int		main(int argc, char **argv)
{
	t_vars		vars;

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
	player_initialise(&vars);
	vars.mlxvars.mlx = mlx_init();
	vars.mlxvars.mlx_win = mlx_new_window(vars.mlxvars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	mlx_loop_hook(vars.mlxvars.mlx, raycasting, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 2, 0L, handle_keys, &vars);
	mlx_hook(vars.mlxvars.mlx_win, 17, 0L, xbutton_close, &vars);
	mlx_loop(vars.mlxvars.mlx);
}

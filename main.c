#include "minilibx/mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define	MAP_WIDTH	10
#define	MAP_HEIGHT	10
#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	400



typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*mlx_win;
}		t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	esc_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(0);
	}
	return(0);
}

int	xbutton_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;
//	int	fd;
//	size_t	bytes;
//	char	*map;
	int	map[MAP_HEIGHT][MAP_WIDTH] =
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

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	img.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int zoom = 10;
	int k = 0;
	int l = 0;

	while (j < SCREEN_HEIGHT && y < MAP_HEIGHT)
	{
		x = 0;
		i = 0;
		while (i < SCREEN_WIDTH)
		{
			k = 0;
			if (x < MAP_WIDTH && map[y][x] == 1)
			{
				while (k < zoom)
				{
					my_mlx_pixel_put(&img, i, j, 0x00FFFFFF);
					k++;
					i++;
				}
				x++;
			}
			else if (x < MAP_WIDTH && map[y][x] == 5)
			{
				while (k < zoom)
				{
					my_mlx_pixel_put(&img, i, j, 0x00FF0000);
					k++;
					i++;
				}
				x++;
			}
			else if (x < MAP_WIDTH && map[y][x] == 0)
			{
				i += zoom;
				x++;
			}
			else
			i++;
		}
		l++;
		j++;
		if (x == MAP_WIDTH && l == zoom)
		{
			y++;
			l = 0;
		}
	}

	mlx_put_image_to_window(vars.mlx, vars.mlx_win, img.img, 0, 0);
	mlx_hook(vars.mlx_win, 2, 0L, esc_close, &vars);
	mlx_hook(vars.mlx_win, 17, 0L, xbutton_close, &vars);
	mlx_loop(vars.mlx);

}

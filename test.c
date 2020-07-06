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
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*mlx_win;
}				t_vars;

int pos_x = 0;
int pos_y = 0;
int zoom = 30;
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	handle_keys(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(0);
	}
	if (keycode == 126 && (map[pos_y - 1][pos_x] == 0 || map[pos_y -1][pos_x] == 5))
		pos_y--;
	if (keycode == 125 && (map[pos_y + 1][pos_x] == 0 || map[pos_y + 1][pos_x] == 5))
		pos_y++;
	if (keycode == 123 && (map[pos_y][pos_x - 1] == 0 || map[pos_y][pos_x - 1] == 5))
		pos_x--;
	if (keycode == 124 && (map[pos_y][pos_x + 1] == 0 || map[pos_y][pos_x + 1] == 5))
		pos_x++;
	printf("tecla: %d\n", keycode);
	return(0);
}

int	xbutton_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

void	print_map(t_data *img)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int k = 0;
	int l = 0;
	int	px = pos_x * zoom;
	int py = pos_y * zoom;

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
					my_mlx_pixel_put(img, i, j, 0x00FFFFFF);
					k++;
					i++;
				}
				x++;
			}
			else if (x < MAP_WIDTH && map[y][x] == 5)
			{
				px = pos_x * zoom;
				while (k < zoom)
				{
					my_mlx_pixel_put(img, px, py, 0x00FF0000);
					k++;
					i++;
					px++;
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
		if (px != pos_x * zoom)
		{
			py++;
		}
		if (x == MAP_WIDTH && l == zoom)
		{
			y++;
			l = 0;
		}
	}
}

void	find_position()
{
	int i = 0;
	int j = 0;
	while (j < MAP_HEIGHT)
	{
		while (i < MAP_WIDTH)
		{
			if (map[j][i] == 5)
			{
				pos_x = i;
				pos_y = j;
				break;
			}
			i++;
		}
		j++;
		i = 0;
	}
}

int prueba(t_vars *vars)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	print_map(&img);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, img.img, 0, 0);
	return(0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

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

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	find_position();
	mlx_loop_hook(vars.mlx, prueba, &vars);
	mlx_hook(vars.mlx_win, 2, 0L, handle_keys, &vars);
	mlx_hook(vars.mlx_win, 17, 0L, xbutton_close, &vars);
	mlx_loop(vars.mlx);

}
